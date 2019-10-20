#include <utility>
#include <thread>
#include <mutex>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/program_options.hpp>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>

#include "../include/config.h"
#include "../include/TrafficeVolumeReduction.h"
#include "../include/PeriodicListPrunning.h"
#include "../include/httplib.h"

using namespace boost::program_options;
using namespace httplib;

string host = "localhost";
bool ssl = false;
int port = 80;
string dns_id;
int payload_count = 1000;

std::vector<Candidate> L;
std::mutex L_mutex;

void timer_start(std::function<void(std::vector<Candidate>&)> func, unsigned int interval, bool cron=false)
{
    std::thread([func, interval, cron]()
    {
        if(cron)
        {
#ifdef DEBUG
            std::this_thread::sleep_for(std::chrono::seconds(interval));
#else
            tm *timeout_tm;
            time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            timeout_tm = gmtime(&now);
            timeout_tm->tm_hour = 0;
            timeout_tm->tm_min = 0;
            timeout_tm->tm_sec = 0;
            timeout_tm->tm_mday += 1;
            time_t timeout_time_t=mktime(timeout_tm);

            std::chrono::system_clock::time_point timeout_tp = std::chrono::system_clock::from_time_t(timeout_time_t);
            std::this_thread::sleep_until(timeout_tp);
#endif
        }
        while (true)
        {
            L_mutex.lock();
            func(L);
            L_mutex.unlock();
#ifdef DEBUG
            std::this_thread::sleep_for(std::chrono::seconds(interval));
#else
            std::this_thread::sleep_for(std::chrono::hours(interval));
#endif
        }
    }).detach();
}


void post(string payload)
{
    std::shared_ptr<Response> res;
    if(ssl)
    {
        httplib::SSLClient cli(host.c_str(), port);
        cli.enable_server_certificate_verification(false);
        res = cli.Post("/", payload, "application/json");
    }
    else
    {
        httplib::Client cli(host.c_str(), port);
        res = cli.Post("/", payload, "application/json");

    }
#ifdef DEBUG
    if (res)
    {
        cout << res->status << endl;
    }
    else
    {
        cout << "Error" << endl;
    }
#endif
}


void convert2json(std::vector<Candidate>& _L)
{
    json jv;
    std::shared_ptr<Response> res;
    int cnt = 0;
    for (Candidate value : _L)
    {
#ifdef ADVANCED
        if (!PeriodicListPrunning::advanced_filter(value)) continue;
#endif
        json j;
        j["dns"] = value.dns;
	    j["time"] = value.t;
        j["domain"] = value.domain;
        j["T"] = value.ttl;
        j["Q"] = value.q;
        json j_set(value.r);
        j["R"] = j_set;
        json j_vec(value.g);
        j["G"] = j_vec;
        jv.push_back(j);
        cnt++;
        if(cnt >= payload_count && jv.size() > 0)
        {
            string payload = jv.dump();
            post(payload);
            cnt = 0;
            jv.clear();
        }
    }
    if (jv.size() > 0)
    {
        string payload = jv.dump();
        post(payload);
    }
    _L.clear();
}


std::set<IP_TYPE> resolveDomain(std::string domain, std::string nameserver="8.8.8.8")
{
    PacketSender sender;
    std::set<IP_TYPE> ips;
    IP pkt = IP(nameserver) / UDP(53, 1337) / DNS();
    pkt.rfind_pdu<DNS>().add_query({ domain, DNS::A, DNS::IN });
    pkt.rfind_pdu<DNS>().recursion_desired(1);
    std::unique_ptr<PDU> response(sender.send_recv(pkt));
    if (response)
    {
        DNS dns = response->rfind_pdu<RawPDU>().to<DNS>();
        for (const auto &record : dns.answers())
        {
            if (record.query_type() == DNS::CNAME)
            {
                std::set<IP_TYPE> _ips = resolveDomain(record.data());
                ips.insert(_ips.begin(), _ips.end());
            }
            if(record.query_type() == DNS::A)
            {
                ips.insert(record.data());
            }
        }
    }
    return ips;
}


bool callback(const PDU& pdu)
{
    DNS dns = pdu.rfind_pdu<RawPDU>().to<DNS>();
    Packet packet = (Packet)pdu;
    DomainInfo _dns;
    _dns.t = packet.timestamp().seconds()*1000000 + packet.timestamp().microseconds();

    TrafficeVolumeReduction tvr;

    for (const auto& answer : dns.answers())
    {
        if (answer.query_type() == DNS::A){
            _dns.domain = boost::algorithm::to_lower_copy(answer.dname());
            trim_left_if(_dns.domain, boost::is_any_of("www."));
            _dns.ttl = answer.ttl();
            _dns.dns = dns_id;
            try
            {
                _dns.ips.insert(answer.data());
            }
            catch(Tins::invalid_address)
            {
#ifdef ERROR
                cout << "error IP:" <<  answer.data() << endl;
#endif
                continue;
            }
        }
        if (answer.query_type() == DNS::CNAME)
        {
            _dns.domain = answer.dname();
            trim_left_if(_dns.domain, boost::is_any_of("www."));
            _dns.ttl = answer.ttl();
            std::set<IP_TYPE> _ips = resolveDomain(answer.data());
            _dns.ips.insert(_ips.begin(), _ips.end());
            _dns.dns = dns_id;
        }
    }
    if(tvr.filter(_dns))
    {
        L_mutex.lock();
        PeriodicListPrunning::push(&L, _dns);
        L_mutex.unlock();
    }
    return true;
}


int main(int argc, char* argv[])
{
    pid_t pid, sid;
    boost::property_tree::ptree pt;

    options_description desc("Allowed options");
    desc.add_options()
            ("help,h", "produce help message")
#ifdef DEBUG
            ("config,c", value<string>()->default_value("passivedns.conf"), "config file path")
#else
    ("config,c", value<string>()->default_value("/etc/passivedns/passivedns.conf"), "config file path")
#endif
            ("ssl,s", "ssl connection")
            ("daemon,d", "daemonize passivedns");

    variables_map vm;
    parsed_options parsed = command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    store(parsed, vm);
    notify(vm);

    /// Help message
    if(vm.count("help"))
    {
        cout << desc << endl;
        return 1;
    }

    //Enable encryption
    if(vm.count("ssl"))
    {
        ssl = true;
    }

    /// Config file path
    string configfile;
    if(vm.count("config"))
    {
        configfile = vm["config"].as<string>();
    }
    boost::property_tree::ini_parser::read_ini(configfile, pt);
    string interface = pt.get<std::string>("Global.interface");
    dns_id = pt.get<std::string>("Global.DNS_ID");
    //Set hostname
    host = pt.get<string>("HTTP.host");
    //Set port
    port = stoi(pt.get<std::string>("HTTP.port"));
    //Set payload count
    payload_count = stoi(pt.get<std::string>("HTTP.payload_count"));

    if(vm.count("daemon"))
    {
        pid = fork();
        if (pid>0)
        {
            exit(EXIT_SUCCESS);
        }
        else if (pid < 0)
        {
            exit(EXIT_FAILURE);
        }
        umask(0);

        openlog("passivedns", LOG_NOWAIT | LOG_PID, LOG_USER);
        syslog(LOG_NOTICE, "Successfully started passivedns");

        sid = setsid();
        if(sid < 0)
        {
            /// Log failure and exit
            syslog(LOG_ERR, "Could not generate session ID for child process");
            exit(EXIT_FAILURE);
        }
        if((chdir("/")) < 0)
        {
            /// Log failure and exit
            syslog(LOG_ERR, "Could not change working directory to /");
            exit(EXIT_FAILURE);
        }
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
#ifdef DEBUG
    timer_start(PeriodicListPrunning::filter, 150);
    timer_start(convert2json, 300, false);
#else
    int upload_hour = stoi(pt.get<std::string>("Global.UPLOAD_HOUR"));
    int cron_time = stoi(pt.get<std::string>("Global.CRON_TIME"));
    timer_start(PeriodicListPrunning::filter, cron_time);
    timer_start(convert2json, upload_hour, true);
#endif
    /// Sniff on the provided interface in promiscuos mode
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    /// Only capture udp packets sent to port 53
    config.set_filter("udp and src port 53");
    Sniffer sniffer(interface, config);
    /// Start the capture
    sniffer.sniff_loop(callback);

    syslog(LOG_NOTICE, "Stopping daemon-name");
    closelog();
    /// Terminate the child process when the daemon completes
    exit(EXIT_SUCCESS);
}

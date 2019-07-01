#include <utility>
#include <tins/tins.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <thread>
#include <mutex>
#include <cppkafka/cppkafka.h>

#include "TrafficeVolumeReduction.h"
#include "PeriodicListPrunning.h"

#ifdef KAFKA
#include "KafkaConnector.h"
#endif

#ifdef DEBUG
#include <ctime>
#endif


using std::cout;
using std::endl;
using json = nlohmann::json;
using namespace cppkafka;

using namespace Tins;
using namespace std;

std::vector<Candidate> L;
std::mutex L_mutex;

void timer_start(std::function<void(std::vector<Candidate>&)> func, unsigned int interval)
{
    PeriodicListPrunning filter2;
    std::thread([func, filter2, interval]() {
        while (true)
        {
            func(L);
            std::this_thread::sleep_for(std::chrono::seconds(interval));
        }
    }).detach();
}


void F2a(std::vector<Candidate>& _L)
{
    L_mutex.lock();
    cout << endl;
#ifdef DEBUG
    for(auto &elem : _L){
        cout << elem.domain << "\t" << elem.ttl << endl;
    }
#endif
    for (std::vector<Candidate>::iterator value=L.begin();value!=L.end();){
        std::set<IP_TYPE> networks;
        for (auto ip : value->r){
            std::vector<std::string> results;
            boost::algorithm::split(results, ip, boost::algorithm::is_any_of("."));
            results[2] = results[3] = '0';
            networks.insert(boost::algorithm::join(results, "."));
        }
        if ((value->q > 100) && (value->g.size() < 3) && ((value->r.size() <= 5) || ((float)(networks.size() / value->r.size()) <= 0.5))){
            ++value;
        }
        else{
            value = L.erase(value);
        }
    }
    L_mutex.unlock();
}

void converttojson(std::vector<Candidate>& _L)
{
#ifdef KAFKA
    KafkaConnector kafka;
#endif

    std::vector<json> jv;
    L_mutex.lock();
    for (Candidate value : L)
    {
        json j;
        j["domain"] = value.domain;
        j["T"] = value.ttl;
        j["Q"] = value.q;
        json j_set(value.r);
        j["R"] = j_set;
        json j_vec(value.g);
        j["G"] = j_vec;
        cout << j << endl;
        jv.push_back(j);
    }
#ifdef KAKFA
    kafka.push(jv);
#endif
    L_mutex.unlock();
}


std::set<IP_TYPE> resolveDomain(std::string domain){
    // The sender
    PacketSender sender;
    std::set<IP_TYPE> ips;
    // The DNS request
    IP pkt = IP("8.8.8.8") / UDP(53, 1337) / DNS();
    // Add the query
    pkt.rfind_pdu<DNS>().add_query({ domain, DNS::A, DNS::IN });
    // We want the query to be resolverd recursively
    pkt.rfind_pdu<DNS>().recursion_desired(1);

    // Send and receive the response.
    std::unique_ptr<PDU> response(sender.send_recv(pkt));
    // Did we receive anything?
    if (response) {
        // Interpret the response
        DNS dns = response->rfind_pdu<RawPDU>().to<DNS>();
        // Print responses
        for (const auto &record : dns.answers()) {
            if (record.query_type() == DNS::CNAME){
                std::set<IP_TYPE> _ips = resolveDomain(record.data());
                ips.insert(_ips.begin(), _ips.end());
            }
            if(record.query_type() == DNS::A){
                ips.insert(record.data());
            }
        }
    }
    return ips;
}


bool callback(const PDU& pdu) {
    DNS dns = pdu.rfind_pdu<RawPDU>().to<DNS>();
    Packet packet = (Packet)pdu;
    std::set<std::string> ips;
    DomainInfo _dns;
    _dns.t = packet.timestamp().seconds();

    TrafficeVolumeReduction tvr;

    for (const auto& answer : dns.answers()){
        if (answer.query_type() == DNS::A){
            _dns.domain = answer.dname();
            _dns.ttl = answer.ttl();
            try{
                _dns.ips.insert(answer.data());
            }
            catch(Tins::invalid_address){
#ifdef ERROR
                cout << "error IP:" <<  answer.data() << endl;
#endif
                continue;
            }
        }
        if (answer.query_type() == DNS::CNAME){
            _dns.domain = answer.dname();
            _dns.ttl = answer.ttl();
            std::set<IP_TYPE> _ips = resolveDomain(answer.data());
            _dns.ips.insert(_ips.begin(), _ips.end());
        }
    }
    if(tvr.F1(_dns)){
        PeriodicListPrunning f2;
        L_mutex.lock();
        f2.push(L, _dns);
        L_mutex.unlock();
    }
    return true;
}



int main(int argc, char* argv[]) {
    if(argc != 2) {
        #ifdef DEBUG
            cout << "Usage: " <<* argv << " <interface>" << endl;
        #endif
        return 1;
    }
    timer_start(F2a, 300);
    // :TODO Set starting process on certain time
    timer_start(converttojson, 10);

    // Sniff on the provided interface in promiscuos mode
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    // Only capture udp packets sent to port 53
    config.set_filter("udp and src port 53");
    Sniffer sniffer(argv[1], config);

    // Start the capture
    sniffer.sniff_loop(callback);
}
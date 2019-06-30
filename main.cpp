#include <tins/tins.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include "TrafficeVolumeReduction.h"
#include "PeriodicListPrunning.h"

#ifdef DEBUG
#include <ctime>
#endif


using std::cout;
using std::endl;
using json = nlohmann::json;

using namespace Tins;

std::vector<Candidate> L;

#ifdef DEBUG
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
#endif

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

            // TODO Add CNAME
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
        #ifdef DEBUG
            cout << "time: " << "\t" << currentDateTime() << endl;
            cout << _dns.domain << "\t" << _dns.ttl << endl;
            PeriodicListPrunning f2;
            f2.push(L, _dns);
        #endif
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

    // Sniff on the provided interface in promiscuos mode
    SnifferConfiguration config;
    config.set_promisc_mode(true);
    // Only capture udp packets sent to port 53
    config.set_filter("udp and src port 53");
    Sniffer sniffer(argv[1], config);

    // Start the capture
    sniffer.sniff_loop(callback);
}
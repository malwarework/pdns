#include <tins/tins.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include "TrafficeVolumeReduction.h"

using std::cout;
using std::endl;
using json = nlohmann::json;

using namespace Tins;


bool callback(const PDU& pdu) {
    DNS dns = pdu.rfind_pdu<RawPDU>().to<DNS>();
    std::vector<std::string> ips;
    json j;

    TrafficeVolumeReduction tvr;

    for (const auto& answer : dns.answers()){
        ips.push_back(answer.data());
        j["domain"] = answer.dname();
        j["ttl"] = answer.ttl();
    }
    j["ips"] = ips;
    if(tvr.F1(j))
        cout << j << endl;
    j.clear();
    return true;
}



int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: " <<* argv << " <interface>" << endl;
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
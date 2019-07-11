//
// Created by user on 29.6.19.
//

#ifndef PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H
#define PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

#include "config.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <tins/tins.h>
#include <ctime>
#include <iostream>

using namespace Tins;
using namespace std;
using json = nlohmann::json;



struct DomainInfo {
    std::string domain;
    unsigned short int ttl;
    std::set<IP_TYPE> ips;
    uint64_t t;
};


class TrafficeVolumeReduction {
private:
    static bool F1a(const DomainInfo&, unsigned short int);
    static bool F1b(const DomainInfo&, unsigned int, unsigned short int);
    static bool F1c(const DomainInfo&);
public:
    bool F1(const DomainInfo&);
};


#endif //PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

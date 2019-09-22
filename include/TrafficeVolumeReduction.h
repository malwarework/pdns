//
// Created by user on 29.6.19.
//

#ifndef PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H
#define PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

#include "config.h"
#include <boost/algorithm/string.hpp>

/// Structure for data domains
struct DomainInfo {
    std::string domain; ///< Domain Name
    std::string dns;    ///< Id of dns server
    unsigned short int ttl; ///< TTL
    std::set<IP_TYPE> ips;  ///< List of IPs
    uint64_t t; ///< Value of time
};


class TrafficeVolumeReduction {
private:
    static bool filter_a(const DomainInfo&, unsigned short int);
    static bool filter_b(const DomainInfo&, unsigned int, unsigned short int);
    static bool filter_c(const DomainInfo&);
public:
    bool filter(const DomainInfo&);
};


#endif //PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

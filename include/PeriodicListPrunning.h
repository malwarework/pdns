//
// Created by user on 30.6.19.
//

#ifndef PASSIVEDNS_PERIODICLISTPRUNNING_H
#define PASSIVEDNS_PERIODICLISTPRUNNING_H

#include "config.h"
#include "TrafficeVolumeReduction.h"

/// Structure of data
struct Candidate{
    std::string domain; ///< Domain name
    std::string dns; ///DNS id of dns server
    uint64_t t; ///< value of time
    unsigned int q=0;   ///< Qi
    unsigned short int ttl; ///< TTL
    std::set<IP_TYPE> r;    ///< Ri
    std::map<uint64_t, unsigned int> g; ///< Gi
};

class PeriodicListPrunning {
public:
    static void push(std::vector<Candidate>&, DomainInfo);
//    void F2(std::vector<Candidate>&, unsigned short int q=100, unsigned short int len_g=3, unsigned short int len_rj=5, float p=0.5);
};


#endif //PASSIVEDNS_PERIODICLISTPRUNNING_H

//
// Created by user on 30.6.19.
//

#ifndef PASSIVEDNS_PERIODICLISTPRUNNING_H
#define PASSIVEDNS_PERIODICLISTPRUNNING_H

#include "config.h"
#include "TrafficeVolumeReduction.h"
#include <ctime>
#include <vector>
#include <iostream>
#include <tins/tins.h>


using namespace std;

struct Candidate{
    std::string domain;
    uint64_t t;
    unsigned int q=0;
    unsigned short int ttl;
    std::set<IP_TYPE> r;
    std::map<uint64_t, unsigned int> g;
};

class PeriodicListPrunning {
public:
    static void push(std::vector<Candidate>&, DomainInfo);
    void F2(std::vector<Candidate>&, unsigned short int q=100, unsigned short int len_g=3, unsigned short int len_rj=5, float p=0.5);

};


#endif //PASSIVEDNS_PERIODICLISTPRUNNING_H

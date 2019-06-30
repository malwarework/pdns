//
// Created by user on 30.6.19.
//

#include "PeriodicListPrunning.h"

void PeriodicListPrunning::push(std::vector<Candidate> &L, DomainInfo domain){
    Candidate candidate;

    bool inArray = false;

    for (Candidate& elem : L){
        if(elem.domain == domain.domain){
            // Set ti
            elem.t = domain.t;
            //Set Qd
            elem.q++;
            //Set max TTL
            elem.ttl = (elem.ttl >= domain.ttl ? elem.ttl : domain.ttl);
            //Set Gd
            //Get IPs till this moment
            std::set<IP_TYPE> diff;
            std::set_difference(domain.ips.begin(), domain.ips.end(), elem.r.begin(), elem.r.end(), std::inserter(diff, diff.begin()));
            if (diff.size() > 0){
                map<uint64_t, unsigned int> tmpmap;
                tmpmap.insert(std::make_pair(domain.t, diff.size()));
                elem.g.push_back(tmpmap);
            }
            //Set Rd
            elem.r.insert(domain.ips.begin(), domain.ips.end());
            inArray = true;
            break;
        }
    }
    if (!inArray){
        //Set domain
        candidate.domain = domain.domain;
        //Set ti
        candidate.t = domain.t;
        //Set Qd
        candidate.q ++;
        //Set max TTL
        candidate.ttl = domain.ttl;
        //Set Rd
        candidate.r = domain.ips;
        //Set Gd
        unsigned int domains_size = domain.ips.size();
        map<uint64_t, unsigned int> tmpmap;
        tmpmap.insert(std::make_pair(domain.t, domains_size));
        candidate.g.push_back(tmpmap);
        L.push_back(candidate);
    }
};

//
// Created by user on 30.6.19.
//

#include "../include/PeriodicListPrunning.h"

void PeriodicListPrunning::push(std::vector<Candidate>* _L, DomainInfo domain)
{
    Candidate candidate;

    bool inArray = false;
    /*
     * :TODO There are problems with calculating Gi and Ri
     */
    for (auto & elem : *_L)
    {
        if(elem.domain == domain.domain)
        {
            // Set dns
            elem.dns = domain.dns;
            // Set ti
            elem.t = domain.t;
            //Set Qd
            elem.q++;
            //Set max TTL
            elem.ttl = (elem.ttl >= domain.ttl ? elem.ttl : domain.ttl);
            //Set Gd
            std::set<IP_TYPE> old_ips = elem.r;
            std::set<IP_TYPE> new_ips = domain.ips;
            std::vector<IP_TYPE> union_ips;

            std::set_union(old_ips.begin(), old_ips.end(), new_ips.begin(), new_ips.end(), std::back_inserter(union_ips));
            int lenips = union_ips.size() - old_ips.size();
            if (lenips > 0)
            {
                elem.g.insert(std::make_pair(domain.t, lenips));
            }

            //Set Rd
            elem.r.insert(domain.ips.begin(), domain.ips.end());
#ifdef DEBUG
            if (elem.g.size() > 1)
            {
                cout << elem.domain << endl;
                json j;
                j["domain"] = elem.dns;
                j["ips"] = elem.r;
                j["G"] = elem.g;
                cout << j.dump() << endl;
            }
#endif
            return;
        }
    }
    // Set dns
    candidate.dns = domain.dns;
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
    candidate.g.insert(std::make_pair(domain.t, domains_size));
    (*_L).push_back(candidate);
};

//
// Created by user on 30.6.19.
//

#include "../include/PeriodicListPrunning.h"

void PeriodicListPrunning::push(std::vector<Candidate>* _L, DomainInfo domain)
{
    Candidate candidate;
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


void PeriodicListPrunning::filter(std::vector<Candidate>& _L)
{
    for (std::vector<Candidate>::iterator value = _L.begin();value != _L.end();)
    {
        std::set<IP_TYPE> networks;
        for (auto ip : value->r)
        {
            std::vector<std::string> results;
            boost::algorithm::split(results, ip, boost::algorithm::is_any_of("."));
            results[2] = results[3] = '0';
            networks.insert(boost::algorithm::join(results, "."));
        }

        if ((value->q > 100) && (value->g.size() < 3) && ((value->r.size() <= 5) || ((float)(networks.size() / value->r.size()) <= 0.5)))
        {
            value = _L.erase(value);
        }
        else
        {
            ++value;
        }
    }
}

bool PeriodicListPrunning::advanced_filter(Candidate value)
{
    std::set<IP_TYPE> networks;
    for (auto ip : value.r)
    {
        std::vector<std::string> results;
        boost::algorithm::split(results, ip, boost::algorithm::is_any_of("."));
        results[2] = results[3] = '0';
        networks.insert(boost::algorithm::join(results, "."));
    }
    float p = (float)(networks.size() / value.r.size());
    if ((value.ttl < 30) || (value.r.size() >= 10) || (value.g.size() >= 5) || ((value.r.size() >= 5) && (p >= 0.8)) || ((p >= 0.5) && (value.ttl <= 3600) && (value.g.size() >= 10)))
    {
        return true;
    }
    else {
        return false;
    }
}

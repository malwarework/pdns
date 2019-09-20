//
// Created by user on 30.6.19.
//

#include "../include/PeriodicListPrunning.h"

void PeriodicListPrunning::push(std::vector<Candidate>* _L, DomainInfo domain){
    Candidate candidate;

    bool inArray = false;
    /*
     * :TODO There are problems with calculating Gi and Ri
     */
    for (auto & elem : *_L)
    {
        if(elem.domain == domain.domain)
        {
//	    cout << elem.domain << endl;
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
	    if (elem.g.size() > 1)
	    {
		cout << elem.domain << endl;
	    	json j;
	    	j["domain"] = elem.dns;
	    	j["ips"] = elem.r;
	    	j["G"] = elem.g;
	    	cout << j.dump() << endl;
	    }
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

//void F2(std::vector<Candidate>& L, unsigned short int q=100, unsigned short int len_g=3, unsigned short int len_rj=5, float p=0.5)
//{
//    for (std::vector<Candidate>::iterator value=L.begin();value!=L.end();){
//        std::set<IP_TYPE> networks;
//        for (auto ip : value->r){
//            std::vector<std::string> results;
//            boost::algorithm::split(results, ip, boost::algorithm::is_any_of("."));
//            results[2] = results[3] = '0';
//            networks.insert(boost::algorithm::join(results, "."));
//        }
//        if ((value->q > q) && (value->g.size() < len_g) && ((value->r.size() <= len_rj) || ((float)(networks.size() / value->r.size()) <= p))){
//            ++value;
//        }
//        else{
//            value = L.erase(value);
//        }
//    }
//}

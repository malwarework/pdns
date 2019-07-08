//
// Created by user on 29.6.19.
//

#include "../include/TrafficeVolumeReduction.h"


bool TrafficeVolumeReduction::F1a(const DomainInfo& obj, unsigned short int ttl=10800){
    return obj.ttl <= ttl;
}

bool TrafficeVolumeReduction::F1b(const DomainInfo& obj, unsigned int lenpd=3, unsigned short int ttl=30){
    return (obj.ips.size() >= lenpd) || (obj.ttl <= ttl);
}

bool TrafficeVolumeReduction::F1c(const DomainInfo& obj){
    std::set<IP_TYPE> networks;
    if (obj.ips.size() == 0)
        return false;
    for (auto ip : obj.ips){
        std::vector<std::string> results;
        boost::algorithm::split(results, ip, boost::algorithm::is_any_of("."));
        results[2] = results[3] = '0';
        networks.insert(boost::algorithm::join(results, "."));
    }
    try{
        return ((float)(networks.size() / obj.ips.size()) >= (float)(1/3));
    }
    catch (exception){
        return false;
    }

}

bool TrafficeVolumeReduction::F1(const DomainInfo& obj) {
    return  F1a(obj) && F1b(obj) && F1c(obj);
}

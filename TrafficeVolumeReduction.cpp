//
// Created by user on 29.6.19.
//

#include "TrafficeVolumeReduction.h"

bool TrafficeVolumeReduction::F1a(const json& obj, int ttl=10800){
    return obj["ttl"] <= ttl;
}

bool TrafficeVolumeReduction::F1b(const json& obj, int lenpd=3, int ttl=30){
    return (obj["ips"].size() >= lenpd) || (obj["ttl"] <= ttl);
}

bool TrafficeVolumeReduction::F1c(const json& obj){

    return true;
}

bool TrafficeVolumeReduction::F1(const json& obj) {
    return  F1a(obj) && F1b(obj) && F1c(obj);
}

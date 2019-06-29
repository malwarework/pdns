//
// Created by user on 29.6.19.
//

#ifndef PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H
#define PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;



class TrafficeVolumeReduction {
private:
    bool F1a(const json&, int);
    bool F1b(const json&, int, int);
    bool F1c(const json&);
public:
    bool F1(const json&);
};


#endif //PASSIVEDNS_TRAFFICEVOLUMEREDUCTION_H

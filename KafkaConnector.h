//
// Created by suv on 01.07.2019.
//

#ifndef PASSIVEDNS_KAFKACONNECTOR_H
#define PASSIVEDNS_KAFKACONNECTOR_H

#include "PeriodicListPrunning.h"
#include "config.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <cppkafka/cppkafka.h>

using json = nlohmann::json;
using namespace cppkafka;

class KafkaConnector {
private:
    Producer *producer;
public:
    KafkaConnector();
    void push(std::vector<json>&);
};


#endif //PASSIVEDNS_KAFKACONNECTOR_H

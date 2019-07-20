#ifndef PASSIVEDNS_KAFKACONNECTOR_H
#define PASSIVEDNS_KAFKACONNECTOR_H

#include "PeriodicListPrunning.h"
#include "config.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <cppkafka/cppkafka.h>

using json = nlohmann::json;
using namespace cppkafka;

/*
 * Class for connecting to kafka
 */
class KafkaConnector {
private:
    std::string topic;
    Configuration config;
public:
    KafkaConnector(std::string, std::string, bool=false, std::string=std::string(), std::string=std::string(), std::string=std::string(), std::string=std::string());
    void push(std::vector<json>&);
};


#endif //PASSIVEDNS_KAFKACONNECTOR_H

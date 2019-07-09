//
// Created by suv on 01.07.2019.
//

#include "../include/KafkaConnector.h"

KafkaConnector::KafkaConnector(std::string broker_list, std::string topic) {
    this->config = {
            { "metadata.broker.list", broker_list}
    };
    this->topic = topic;

}


void KafkaConnector::push(std::vector<json>& L)
{
    Producer producer(this->config);
    for (json value : L)
    {
        string payload = value.dump();
        producer.produce(MessageBuilder(this->topic).payload(payload));
    }
}
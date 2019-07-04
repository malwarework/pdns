//
// Created by suv on 01.07.2019.
//

#include "KafkaConnector.h"

KafkaConnector::KafkaConnector(std::string broker_list, std::string topic) {
    Configuration config = {
            { "metadata.broker.list", broker_list}
    };
    this->producer = new Producer(config);
    this->topic = topic;

}

void KafkaConnector::push(std::vector<json>& L)
{
    for (json value : L)
    {
        string payload = value.dump();
        this->producer->produce(MessageBuilder(this->topic).payload(payload));
    }
}

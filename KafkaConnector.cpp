//
// Created by suv on 01.07.2019.
//

#include "KafkaConnector.h"

KafkaConnector::KafkaConnector() {
    Configuration config = {
            { "metadata.broker.list", "1.broker.kafka.prod:9092,2.broker.kafka.prod:9092,3.broker.kafka.prod:9092,4.broker.kafka.prod:9092,5.broker.kafka.prod:9092" }
    };
    this.producer(config);
}

void KafkaConnector::push(std::vector<json>& L)
{
    for (auto value : L)
    {
        this->producer.produce(MessageBuilder("CLICK_HOUSE_FASTFLUX_PDNS").payload(value));
    }
}

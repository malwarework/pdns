#include "../include/KafkaConnector.h"

KafkaConnector::KafkaConnector(std::string broker_list, std::string topic, bool ssl, std::string ca, std::string certificate, std::string key, std::string password) {
    if (!ssl)
    {
        this->config = {
                { "metadata.broker.list", broker_list}
        };
    } else{
        this->config = {
                { "metadata.broker.list", broker_list},
                {"security.protocol", "ssl"},
                {"ssl.ca.location", ca},
                {"ssl.certificate.location", certificate},
                {"ssl.key.location", key},
                {"ssl.key.password", password}
        };
    }

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

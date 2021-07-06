#ifndef MQTT_BRIDGEKEEPALIVE_H
#define MQTT_BRIDGEKEEPALIVE_H

#include <chrono>
#include <string>

#include "mqtt-client/mqtt-messages/mqtt_message.h"

class Mqtt_BridgeKeepAlive : public MqttMessage
{
	static const std::string TOPIC;

public:
	Mqtt_BridgeKeepAlive(const std::string& topic_prefix, const std::chrono::seconds uptime);
	virtual ~Mqtt_BridgeKeepAlive();

private:
	virtual MqttMessage::DataBufferPtr Generate() const;

private:
	const std::chrono::seconds m_Uptime;
};

#endif // MQTT_BRIDGEKEEPALIVE_H

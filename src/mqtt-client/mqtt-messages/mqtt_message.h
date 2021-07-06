#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H

#include "mqtt/message.h"
#include "mqtt/topic.h"

#include <memory>
#include <string>
#include <utility>

#include "mqtt-client/mqtt_qos.h"

class MqttMessage
{
public:
	MqttMessage(const std::string& topic, const MqttQosLevels qos_level = MqttQosLevels::AtMostOnce, bool retained = false);
	virtual ~MqttMessage();

public:
	mqtt::message_ptr Message() const;

protected:
	using DataBufferPtr = std::pair<std::shared_ptr<uint8_t[]>, std::size_t>;
	virtual DataBufferPtr Generate() const = 0;

protected:
	const std::string m_Topic;
	const MqttQosLevels m_QosLevel;
	const bool m_Retained;
};

#endif // MQTT_MESSAGE_H

#include <boost/log/trivial.hpp>

#include "mqtt-client/mqtt-messages/mqtt_message.h"

MqttMessage::MqttMessage(const std::string& topic, const MqttQosLevels qos_level, bool retained) :
	m_Topic(topic),
	m_QosLevel(qos_level),
	m_Retained(retained)
{
}

MqttMessage::~MqttMessage()
{
}

mqtt::message_ptr MqttMessage::Message() const
{
	mqtt::message message;

	if (auto payload = Generate(); nullptr != payload.first)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Constructing MQTT message payload - length: " << payload.second << L" bytes";
		return mqtt::make_message(m_Topic, payload.first.get(), payload.second, static_cast<int>(m_QosLevel), m_Retained);
	}
	else
	{
		BOOST_LOG_TRIVIAL(trace) << L"Constructing MQTT message payload - zero length payload?";
		return mqtt::make_message(m_Topic, "", static_cast<int>(m_QosLevel), m_Retained);
	}
}

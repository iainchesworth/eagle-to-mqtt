#include <boost/log/trivial.hpp>
#include <mqtt/topic.h>

#include "mqtt-client/mqtt-messages/mqtt_bridgekeepalive.h"
#include "mqtt-client/mqtt_qos.h"

const std::string Mqtt_BridgeKeepAlive::TOPIC{ "/bridge/uptime" };

Mqtt_BridgeKeepAlive::Mqtt_BridgeKeepAlive(const std::string& topic_prefix, const std::chrono::seconds uptime) :
	MqttMessage(topic_prefix+TOPIC, MqttQosLevels::AtLeastOnce),
	m_Uptime(uptime)
{
	BOOST_LOG_TRIVIAL(trace) << L"Building Mqtt_BridgeKeepAlive payload";
}

Mqtt_BridgeKeepAlive::~Mqtt_BridgeKeepAlive()
{
}

MqttMessage::DataBufferPtr Mqtt_BridgeKeepAlive::Generate() const
{
	auto raw_payload = std::to_string(m_Uptime.count());
	auto raw_payload_length = raw_payload.length();

	auto payload_ptr = std::shared_ptr<uint8_t[]>(new uint8_t[raw_payload_length]);
	auto payload = std::make_pair(payload_ptr, raw_payload_length);

	std::memcpy(payload.first.get(), raw_payload.data(), raw_payload_length);

	return payload;
}

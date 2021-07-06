#include <boost/log/trivial.hpp>
#include <mqtt/topic.h>

#include <memory>
#include <sstream>

#include "mqtt-client/mqtt-messages/mqtt_bridgestatuschanged.h"
#include "mqtt-client/mqtt_qos.h"

const std::string Mqtt_BridgeStatusChanged::TOPIC{ "/bridge/status" };

Mqtt_BridgeStatusChanged::Mqtt_BridgeStatusChanged(const std::string& topic_prefix, const BridgeStatus status) :
	MqttMessage(topic_prefix + TOPIC, MqttQosLevels::AtLeastOnce),
	m_Status(status)
{
	BOOST_LOG_TRIVIAL(trace) << L"Building Mqtt_BridgeStatusChanged payload";
}

Mqtt_BridgeStatusChanged::~Mqtt_BridgeStatusChanged()
{
}

MqttMessage::DataBufferPtr Mqtt_BridgeStatusChanged::Generate() const
{
	std::ostringstream payload_oss;
	payload_oss << m_Status;

	auto raw_payload = payload_oss.str();
	auto raw_payload_length = raw_payload.length();

	auto payload_ptr = std::shared_ptr<uint8_t[]>(new uint8_t[raw_payload_length]);
	auto payload = std::make_pair(payload_ptr, raw_payload_length);

	std::memcpy(payload.first.get(), raw_payload.data(), raw_payload_length);

	return payload;
}

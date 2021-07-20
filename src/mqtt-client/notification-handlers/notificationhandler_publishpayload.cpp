#include <string>

#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt_qos.h"
#include "notifications/common/metering_payload_types.h"

void MqttConnection::NotificationHandler_PublishPayload(const std::string& topic_prefix, const MeteringPayload& metering_payload)
{
	for (auto& [key, value] : metering_payload.second)
	{
		auto topic = topic_prefix + key;

		std::ostringstream payload_oss;
		payload_oss << value;

		Publish(
			mqtt::message_ptr_builder()
			.topic(topic)
			.payload(payload_oss.str())
			.qos(static_cast<int>(MqttQosLevels::AtMostOnce))
			.retained(false)
			.finalize()
		);
	}
}

#include <spdlog/spdlog.h>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/common/metering_payload_types.h"

void MqttConnection::NotificationHandler_DeviceInfo(const MeteringPayload& metering_payload)
{
	spdlog::trace("NotificationHandler_DeviceInfo() -> Notification received by MQTT Connection");

	if (nullptr == m_ClientPtr)
	{
		spdlog::warn("MQTT client was null; cannot send DeviceInfo message to broker");
	}
	else if (!m_ClientPtr->is_connected())
	{
		spdlog::debug("MQTT client is not connected; cannot send DeviceInfo message to broker");
	}
	else
	{
		const std::string TOPIC{ m_Options.MqttTopic() + "/" + MeteringPayload_DeviceId::ToString(metering_payload.first) + "/"};
		NotificationHandler_PublishPayload(TOPIC, metering_payload);
	}
}

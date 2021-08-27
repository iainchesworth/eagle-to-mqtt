#include <spdlog/spdlog.h>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/common/notification_payload_types.h"

void MqttConnection::NotificationHandler_EnergyGeneration(const SymoNotification_PublishPayload::Types::Payload& metering_payload)
{
	spdlog::trace("NotificationHandler_EnergyGeneration() -> Notification received by MQTT Connection");

	if (nullptr == m_ClientPtr)
	{
		spdlog::warn("MQTT client was null; cannot send EnergyUsage message to broker");
	}
	else if (!m_ClientPtr->is_connected())
	{
		spdlog::debug("MQTT client is not connected; cannot send EnergyUsage message to broker");
	}
	else
	{
		const std::string TOPIC{ m_Options.MqttTopic() + "/power/generation/" };
		NotificationHandler_PublishPayload(TOPIC, metering_payload);
	}
}

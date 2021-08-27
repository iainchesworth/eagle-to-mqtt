#include <spdlog/spdlog.h>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/common/notification_payload_types.h"

void MqttConnection::NotificationHandler_InverterInfo(const SymoNotification_PublishPayload::Types::Payload& metering_payload)
{
	spdlog::trace("NotifcationHandler_InverterInfo() -> Notification received by MQTT Connection");

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
		const std::string TOPIC{ m_Options.MqttTopic() + "/inverters/" + std::to_string(metering_payload.first) + "/" };
		NotificationHandler_PublishPayload(TOPIC, metering_payload);
	}
}

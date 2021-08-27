#include <spdlog/spdlog.h>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/common/notification_payload_types.h"

void MqttConnection::NotificationHandler_InverterStatus(const SymoNotification_PublishPayload::Types::Payload& metering_payload)
{
	spdlog::trace("NotificationHandler_InverterStatus() -> Notification received by MQTT Connection");

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
		const std::string INVERTER_ID{ "inverter_" + std::to_string(metering_payload.first)};
		const std::string TOPIC{ m_Options.MqttTopic() + "/hardware/inverters/" + INVERTER_ID + "/" };

		NotificationHandler_PublishPayload(TOPIC, metering_payload);
	}
}

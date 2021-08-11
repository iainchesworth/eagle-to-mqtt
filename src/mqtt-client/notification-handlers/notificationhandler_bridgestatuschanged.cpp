#include <spdlog/spdlog.h>

#include "bridge/bridge_status.h"
#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt_qos.h"
#include "notifications/bridge/notification_bridgestatuschanged.h"

void MqttConnection::NotificationHandler_BridgeStatusChange(const BridgeStatus& bridge_status)
{
	spdlog::trace("Notification_BridgeStatusChange() -> Notification received by MQTT Connection");

	const std::string TOPIC{ m_Options.MqttTopic() + "/bridge/status" }; 
	
	std::ostringstream payload_oss;
	payload_oss << bridge_status;

	auto message = mqtt::message_ptr_builder()
		.topic(TOPIC)
		.payload(payload_oss.str())
		.qos(static_cast<int>(MqttQosLevels::AtMostOnce))
		.retained(false)
		.finalize();

	if (nullptr == m_ClientPtr)
	{
		spdlog::warn("MQTT client was null; cannot send BridgeStatusChange message to broker");
	}
	else if (!m_ClientPtr->is_connected())
	{
		spdlog::debug("MQTT client is not connected; cannot send BridgeStatusChange message to broker");

		std::scoped_lock guard(m_QueuedSendOnConnectMutex);
		m_QueuedSendOnConnect[typeid(Notification_BridgeStatusChanged)] = message;
	}
	else
	{
		Publish(message);
	}
}

#include <date/date.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <sstream>

#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt_qos.h"

void MqttConnection::NotificationHandler_PublishKeepAlive(const std::chrono::seconds& uptime)
{
	spdlog::trace("Notification_PublishKeepAlive() -> Notification received by MQTT Connection");

	if (nullptr == m_ClientPtr)
	{
		spdlog::warn("MQTT client was null; cannot send PublishKeepAlive message to broker");
	}
	else if (!m_ClientPtr->is_connected())
	{
		spdlog::debug("MQTT client is not connected; cannot send PublishKeepAlive message to broker");
	}
	else
	{
		using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

		const std::string TOPIC{ m_Options.MqttTopic() + "/bridge/uptime" };

		std::ostringstream oss;
		oss << uptime;

		Publish(
			mqtt::message_ptr_builder()
			.topic(TOPIC)
			.payload(oss.str())
			.qos(static_cast<int>(MqttQosLevels::AtMostOnce))
			.retained(false)
			.finalize()
		);
	}
}

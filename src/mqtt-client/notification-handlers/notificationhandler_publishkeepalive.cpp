#include <boost/log/trivial.hpp>

#include <chrono>

#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt_qos.h"

void MqttConnection::NotificationHandler_PublishKeepAlive(const std::chrono::seconds& uptime)
{
	BOOST_LOG_TRIVIAL(trace) << L"Notification_PublishKeepAlive() -> Notification received by MQTT Connection";

	if (nullptr == m_ClientPtr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"MQTT client was null; cannot send PublishKeepAlive message to broker";
	}
	else if (!m_ClientPtr->is_connected())
	{
		BOOST_LOG_TRIVIAL(debug) << L"MQTT client is not connected; cannot send PublishKeepAlive message to broker";
	}
	else
	{
		const std::string TOPIC{ m_Options.MqttTopic() + "/bridge/uptime" };

		Publish(
			mqtt::message_ptr_builder()
			.topic(TOPIC)
			.payload(std::to_string(uptime.count()))
			.qos(static_cast<int>(MqttQosLevels::AtMostOnce))
			.retained(false)
			.finalize()
		);
	}
}

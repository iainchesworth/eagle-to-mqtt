#include <boost/log/trivial.hpp>

#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt-messages/mqtt_bridgekeepalive.h"

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
		Publish(std::make_shared<Mqtt_BridgeKeepAlive>(m_Options.MqttTopic(), uptime));
	}
}

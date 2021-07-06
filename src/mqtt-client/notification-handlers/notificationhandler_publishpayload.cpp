#include <boost/log/trivial.hpp>

#include "mqtt-client/mqtt_connection.h"

void MqttConnection::NotificationHandler_PublishPayload()
{
	BOOST_LOG_TRIVIAL(trace) << L"Notification_PayloadToPublish() -> Notification received by MQTT Connection";

	if (nullptr == m_ClientPtr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"MQTT client was null; cannot send PublishPayload message to broker";
	}
	else if (!m_ClientPtr->is_connected())
	{
		BOOST_LOG_TRIVIAL(debug) << L"MQTT client is not connected; cannot send PublishPayload message to broker";
	}
	else
	{

	}
}

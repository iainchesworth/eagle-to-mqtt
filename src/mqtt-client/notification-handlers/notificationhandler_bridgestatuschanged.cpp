#include <boost/log/trivial.hpp>

#include "bridge/bridge_status.h"
#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt-messages/mqtt_bridgestatuschanged.h"

void MqttConnection::NotificationHandler_BridgeStatusChange(const BridgeStatus& bridge_status)
{
	BOOST_LOG_TRIVIAL(trace) << L"Notification_BridgeStatusChange() -> Notification received by MQTT Connection";
	auto message = std::make_shared<Mqtt_BridgeStatusChanged>(m_Options.MqttTopic(), bridge_status);

	if (nullptr == m_ClientPtr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"MQTT client was null; cannot send BridgeStatusChange message to broker";
	}
	else if (!m_ClientPtr->is_connected())
	{
		BOOST_LOG_TRIVIAL(debug) << L"MQTT client is not connected; cannot send BridgeStatusChange message to broker";

		std::lock_guard<std::mutex> guard(m_QueuedSendOnConnectMutex);
		m_QueuedSendOnConnect[typeid(Mqtt_BridgeStatusChanged)] = message;
	}
	else
	{
		Publish(message);
	}
}

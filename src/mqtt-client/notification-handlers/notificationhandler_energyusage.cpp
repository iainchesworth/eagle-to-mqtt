#include <boost/log/trivial.hpp>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/common/metering_payload_types.h"

void MqttConnection::NotificationHandler_EnergyUsage(const MeteringPayload& metering_payload)
{
	BOOST_LOG_TRIVIAL(trace) << L"NotificationHandler_EnergyUsage() -> Notification received by MQTT Connection";

	if (nullptr == m_ClientPtr)
	{
		BOOST_LOG_TRIVIAL(warning) << L"MQTT client was null; cannot send EnergyUsage message to broker";
	}
	else if (!m_ClientPtr->is_connected())
	{
		BOOST_LOG_TRIVIAL(debug) << L"MQTT client is not connected; cannot send EnergyUsage message to broker";
	}
	else
	{
		const std::string TOPIC{ m_Options.MqttTopic() + "/" + MeteringPayload_DeviceId::ToString(metering_payload.first) + "/energy-usage/" };
		NotificationHandler_PublishPayload(TOPIC, metering_payload);
	}
}

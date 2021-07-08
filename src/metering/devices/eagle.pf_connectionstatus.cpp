#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_connectivity.h"
#include "notifications/metering/notification_deviceinfo.h"

void Eagle::ProcessFragment(const ConnectionStatus& connection_status)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter connection details and statistics";

	auto connection_status_notif = std::make_shared<Notification_Connectivity>(m_EthernetMacId);

	if (!connection_status.DeviceMacId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee End Device (ZED) id in message payload";
	}
	else if (!connection_status.DeviceMacId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee End Device (ZED) id in message payload";
	}
	else if (m_ZigbeeMacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee End Device (ZED) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee End Device (ZED) id for Eagle: " << ZigBeeMacId::ToString(connection_status.DeviceMacId().value());
		m_ZigbeeMacId = connection_status.DeviceMacId().value();

		auto device_info_notif = std::make_shared<Notification_DeviceInfo>(m_EthernetMacId);
		device_info_notif->Device_MacId(m_ZigbeeMacId);
		NotificationManagerSingleton()->Dispatch(device_info_notif);
	}

	if (!connection_status.Meter_MacId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing meter Zigbee MAC id in message payload";
	}
	else if (!connection_status.Meter_MacId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid meter Zigbee MAC id in message payload";
	}
	else if (m_Connectivity.ZigBee.Meter_MacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid meter Zigbee MAC id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee MAC id of meter connected with Eagle: " << ZigBeeMacId::ToString(connection_status.Meter_MacId().value());
		m_Connectivity.ZigBee.Meter_MacId = connection_status.Meter_MacId().value();
		connection_status_notif->Meter_MacId(m_Connectivity.ZigBee.Meter_MacId);
	}

	if (!connection_status.Extended_PanId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee network extended PAN id in message payload";
	}
	else if (!connection_status.Extended_PanId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee network extended PAN id in message payload";
	}
	else if (m_Connectivity.ZigBee.Extended_PanId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee network extended PAN id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee network extended PAN id: " << ZigBeeMacId::ToString(connection_status.Extended_PanId().value());
		m_Connectivity.ZigBee.Extended_PanId = connection_status.Extended_PanId().value();
		connection_status_notif->Extended_PanId(m_Connectivity.ZigBee.Extended_PanId);
	}

	if (connection_status.Status().has_value())
	{
		m_Connectivity.Status = connection_status.Status().value();
		connection_status_notif->Status(m_Connectivity.Status);
	}
	if (connection_status.Channel().has_value())
	{
		m_Connectivity.Channel = connection_status.Channel().value();
		connection_status_notif->Channel(m_Connectivity.Channel);
	}
	if (connection_status.LinkStrength().has_value())
	{
		m_Connectivity.LinkStrength = connection_status.LinkStrength().value();
		connection_status_notif->LinkStrength(m_Connectivity.LinkStrength);
	}

	NotificationManagerSingleton()->Dispatch(connection_status_notif);
}

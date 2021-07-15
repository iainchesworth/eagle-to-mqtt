#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_connectivity.h"
#include "notifications/metering/notification_deviceinfo.h"

void Eagle::ProcessFragment(const NetworkInfo& network_info)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter connection details and statistics";

	auto connection_status_notif = std::make_shared<Notification_Connectivity>(m_EthernetMacId);

	if (!network_info.DeviceMacId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee End Device (ZED) id in message payload";
	}
	else if (!network_info.DeviceMacId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee End Device (ZED) id in message payload";
	}
	else if (m_ZigbeeMacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee End Device (ZED) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee End Device (ZED) id for Eagle: " << ZigBeeMacId::ToString(network_info.DeviceMacId().value());
		m_ZigbeeMacId = network_info.DeviceMacId().value();

		auto device_info_notif = std::make_shared<Notification_DeviceInfo>(m_EthernetMacId);
		device_info_notif->Device_MacId(m_ZigbeeMacId);
		NotificationManagerSingleton()->Dispatch(device_info_notif);

	}

	if (!network_info.CoordinatorZigbeeId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee Coordinator (ZC) id in message payload";
	}
	else if (!network_info.CoordinatorZigbeeId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee Coordinator (ZC) id in message payload";
	}
	else if (m_Connectivity.ZigBee.Meter_MacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee Coordinator (ZC) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee Coordinator (ZC) id of device forming root with Eagle: " << ZigBeeMacId::ToString(network_info.CoordinatorZigbeeId().value());
		m_Connectivity.ZigBee.Meter_MacId = network_info.CoordinatorZigbeeId().value();
		connection_status_notif->Meter_MacId(m_Connectivity.ZigBee.Meter_MacId);
	}

	if (network_info.Status().has_value())
	{
		m_Connectivity.Status = network_info.Status().value();
		connection_status_notif->Status(m_Connectivity.Status);
	}
	if (network_info.Channel().has_value())
	{
		m_Connectivity.Channel = network_info.Channel().value();
		connection_status_notif->Channel(m_Connectivity.Channel);
	}
	if (network_info.LinkStrength().has_value())
	{
		m_Connectivity.LinkStrength = network_info.LinkStrength().value();
		connection_status_notif->LinkStrength(m_Connectivity.LinkStrength);
	}

	NotificationManagerSingleton()->Dispatch(connection_status_notif);
}

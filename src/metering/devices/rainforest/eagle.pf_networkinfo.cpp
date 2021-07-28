#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"
#include "metering/devices/rainforest/zigbee_id_handler.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_connectivity.h"
#include "notifications/metering/notification_deviceinfo.h"

void Eagle::ProcessFragment(const NetworkInfo& network_info)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter connection details and statistics";

	auto connection_status_notif = std::make_shared<Notification_Connectivity>(m_EthernetMacId);

	ProcessAndSaveZigbeeId(
		m_EthernetMacId,
		network_info.DeviceMacId(),
		m_ZigbeeMacId,
		std::string("Zigbee End Device (ZED)"),
		std::make_shared<Notification_DeviceInfo>(m_EthernetMacId),
		&Notification_DeviceInfo::Device_MacId
	);

	ProcessAndSaveZigbeeId(
		m_EthernetMacId,
		network_info.CoordinatorZigbeeId(),
		m_Connectivity.ZigBee.Meter_MacId,
		std::string("Zigbee Coordinator (ZC)"),
		connection_status_notif,
		&Notification_Connectivity::Meter_MacId
	);

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

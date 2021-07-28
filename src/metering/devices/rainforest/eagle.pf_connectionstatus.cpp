#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"
#include "metering/devices/rainforest/zigbee_id_handler.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_connectivity.h"
#include "notifications/metering/notification_deviceinfo.h"

void Eagle::ProcessFragment(const ConnectionStatus& connection_status)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter connection details and statistics";

	auto connection_status_notif = std::make_shared<Notification_Connectivity>(m_EthernetMacId);

	ProcessAndSaveZigbeeId(
		m_EthernetMacId, 
		connection_status.Meter_MacId(), 
		m_ZigbeeMacId, 
		std::string("Zigbee End Device (ZED)"), 
		std::make_shared<Notification_DeviceInfo>(m_EthernetMacId), 
		&Notification_DeviceInfo::Device_MacId
	);
	
	ProcessAndSaveZigbeeId(
		m_EthernetMacId, 
		connection_status.DeviceMacId(), 
		m_Connectivity.ZigBee.Meter_MacId, 
		std::string("meter Zigbee MAC"), 
		connection_status_notif, 
		&Notification_Connectivity::Meter_MacId
	);

	ProcessAndSaveZigbeeId(
		m_EthernetMacId, 
		connection_status.Extended_PanId(), 
		m_Connectivity.ZigBee.Extended_PanId, 
		std::string("Zigbee network extended PAN"), 
		connection_status_notif, 
		&Notification_Connectivity::Extended_PanId
	);

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

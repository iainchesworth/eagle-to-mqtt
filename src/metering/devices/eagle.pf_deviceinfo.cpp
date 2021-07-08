#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_deviceinfo.h"

void Eagle::ProcessFragment(const DeviceInfo& device_info)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing model id and version information";

	auto device_info_notif = std::make_shared<Notification_DeviceInfo>(m_EthernetMacId);

	if (device_info.FirmwareVersion().has_value())
	{
		m_FirmwareVersion = device_info.FirmwareVersion().value();
		device_info_notif->FirmwareVersion(m_FirmwareVersion);
	}
	if (device_info.HardwareVersion().has_value())
	{
		m_HardwareVersion = device_info.HardwareVersion().value();
		device_info_notif->HardwareVersion(m_HardwareVersion);
	}
	if (device_info.ModelId().has_value())
	{
		m_ModelId = device_info.ModelId().value();
		device_info_notif->ModelId(m_ModelId);
	}

	NotificationManagerSingleton()->Dispatch(device_info_notif);
}

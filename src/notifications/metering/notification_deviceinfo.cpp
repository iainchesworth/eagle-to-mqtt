#include "notifications/metering/notification_deviceinfo.h"

Notification_DeviceInfo::Notification_DeviceInfo(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_DeviceInfo& Notification_DeviceInfo::Device_MacId(const ZigBeeMacId& device_macid)
{
	m_ElementsMap.insert(std::make_pair("zigbee_id", device_macid));
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::FirmwareVersion(const std::string& firmware_version)
{
	m_ElementsMap.insert(std::make_pair("firmware", firmware_version));
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::HardwareVersion(const std::string& hardware_version)
{
	m_ElementsMap.insert(std::make_pair("hardware", hardware_version));
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::ModelId(const std::string& model_id)
{
	m_ElementsMap.insert(std::make_pair("model", model_id));
	return *this;
}

void Notification_DeviceInfo::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	Notification_PublishPayload::Notify(signal);
}

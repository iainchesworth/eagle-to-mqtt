#include "notifications/metering/notification_deviceinfo.h"

const std::string Notification_DeviceInfo::MAPKEY_DEVICEMACID{ "zigbee_id" };
const std::string Notification_DeviceInfo::MAPKEY_FIRMWAREVERSION{ "firmware" };
const std::string Notification_DeviceInfo::MAPKEY_HARDWAREVERSION{ "hardware" };
const std::string Notification_DeviceInfo::MAPKEY_MODELID{ "model" };

Notification_DeviceInfo::Notification_DeviceInfo(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_DeviceInfo& Notification_DeviceInfo::Device_MacId(const ZigBeeMacId& device_macid)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DEVICEMACID, device_macid);
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::FirmwareVersion(const std::string& firmware_version)
{
	m_ElementsMap.insert_or_assign(MAPKEY_FIRMWAREVERSION, firmware_version);
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::HardwareVersion(const std::string& hardware_version)
{
	m_ElementsMap.insert_or_assign(MAPKEY_HARDWAREVERSION, hardware_version);
	return *this;
}

Notification_DeviceInfo& Notification_DeviceInfo::ModelId(const std::string& model_id)
{
	m_ElementsMap.insert_or_assign(MAPKEY_MODELID, model_id);
	return *this;
}

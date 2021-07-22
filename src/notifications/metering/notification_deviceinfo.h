#ifndef NOTIFICATION_DEVICEINFO_H
#define NOTIFICATION_DEVICEINFO_H

#include <boost/signals2/signal.hpp>

#include <string>

#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_DeviceInfo : public Notification_PublishPayload
{
	static const std::string MAPKEY_DEVICEMACID;
	static const std::string MAPKEY_FIRMWAREVERSION;
	static const std::string MAPKEY_HARDWAREVERSION;
	static const std::string MAPKEY_MODELID;

public:
	explicit Notification_DeviceInfo(EthernetMacId device_id);

public:
	Notification_DeviceInfo& Device_MacId(const ZigBeeMacId& device_macid);
	Notification_DeviceInfo& FirmwareVersion(const std::string& firmware_version);
	Notification_DeviceInfo& HardwareVersion(const std::string& hardware_version);
	Notification_DeviceInfo& ModelId(const std::string& model_id);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_DEVICEINFO_H

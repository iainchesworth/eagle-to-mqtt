#ifndef NOTIFICATION_INVERTERSTATUS_H
#define NOTIFICATION_INVERTERSTATUS_H

#include <boost/signals2/signal.hpp>

#include <cstdint>
#include <string>

#include "metering/devices/fronius/messages_types/battery_modes.h"
#include "metering/devices/fronius/messages_types/percentage.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_InverterStatus : public SymoNotification_PublishPayload
{
	static const std::string MAPKEY_DEVICETYPE;
	static const std::string MAPKEY_STATEOFCHARGE;
	static const std::string MAPKEY_COMPONENTID;
	static const std::string MAPKEY_BATTERYMODE;

public:
	Notification_InverterStatus(SymoNotification_PublishPayload::Types::DeviceId device_id);

public:
	Notification_InverterStatus& DeviceType(const int32_t device_type);
	Notification_InverterStatus& StateOfCharge(const Percentage& state_of_charge);
	Notification_InverterStatus& ComponentId(const uint32_t component_id);
	Notification_InverterStatus& BatteryMode(const BatteryModes& battery_mode);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_INVERTERSTATUS_H

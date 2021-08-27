#include "notifications/metering/notification_inverterstatus.h"

const std::string Notification_InverterStatus::MAPKEY_DEVICETYPE{ "DeviceType" };
const std::string Notification_InverterStatus::MAPKEY_STATEOFCHARGE{ "StateOfCharge" };
const std::string Notification_InverterStatus::MAPKEY_COMPONENTID{ "ComponentId" };
const std::string Notification_InverterStatus::MAPKEY_BATTERYMODE{ "BatteryMode" };

Notification_InverterStatus::Notification_InverterStatus(SymoNotification_PublishPayload::Types::DeviceId device_id) :
	SymoNotification_PublishPayload(device_id)
{
}

Notification_InverterStatus& Notification_InverterStatus::DeviceType(const int32_t device_type)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DEVICETYPE, device_type);
	return *this;
}

Notification_InverterStatus& Notification_InverterStatus::StateOfCharge(const Percentage& state_of_charge)
{
	m_ElementsMap.insert_or_assign(MAPKEY_STATEOFCHARGE, state_of_charge);
	return *this;
}

Notification_InverterStatus& Notification_InverterStatus::ComponentId(const uint32_t component_id)
{
	m_ElementsMap.insert_or_assign(MAPKEY_COMPONENTID, component_id);
	return *this;
}

Notification_InverterStatus& Notification_InverterStatus::BatteryMode(const BatteryModes& battery_mode)
{
	m_ElementsMap.insert_or_assign(MAPKEY_BATTERYMODE, battery_mode);
	return *this;
}

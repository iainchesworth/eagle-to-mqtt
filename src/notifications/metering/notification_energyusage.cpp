#include "notifications/metering/notification_energyusage.h"

const std::string  Notification_EnergyUsage::MAPKEY_INSTANTANEOUSDEMAND{ "instantaneous_watts" };
const std::string  Notification_EnergyUsage::MAPKEY_LIFETIMEDELIVERED{ "lifetimedelivered_kwh" };
const std::string  Notification_EnergyUsage::MAPKEY_LIFETIMERECEIVED{ "lifetimereceived_kwh" };

Notification_EnergyUsage::Notification_EnergyUsage(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_EnergyUsage& Notification_EnergyUsage::InstantaneousDemand(const Power& now)
{
	m_ElementsMap.insert_or_assign(MAPKEY_INSTANTANEOUSDEMAND, now.ValueIn<Watts>());
	return *this;
}

Notification_EnergyUsage& Notification_EnergyUsage::LifetimeDelivered(const Usage& delivered)
{
	m_ElementsMap.insert_or_assign(MAPKEY_LIFETIMEDELIVERED, delivered.ValueIn<KilowattHours>());
	return *this;
}

Notification_EnergyUsage& Notification_EnergyUsage::LifetimeReceived(const Usage& received)
{
	m_ElementsMap.insert_or_assign(MAPKEY_LIFETIMERECEIVED, received.ValueIn<KilowattHours>());
	return *this;
}

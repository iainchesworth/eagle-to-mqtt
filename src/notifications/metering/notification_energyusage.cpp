#include "notifications/metering/notification_energyusage.h"

Notification_EnergyUsage::Notification_EnergyUsage(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_EnergyUsage& Notification_EnergyUsage::InstantaneousDemand(const Demand& now)
{
	m_ElementsMap.insert(std::make_pair("instantaneous_watts", now.EnergyValue(UnitsOfMeasure::Units::Watts)));
	return *this;
}

Notification_EnergyUsage& Notification_EnergyUsage::LifetimeDelivered(const Summation& delivered)
{
	m_ElementsMap.insert(std::make_pair("lifetimedelivered_kwh", delivered.EnergyValue()));
	return *this;
}

Notification_EnergyUsage& Notification_EnergyUsage::LifetimeReceived(const Summation& received)
{
	m_ElementsMap.insert(std::make_pair("lifetimereceived_kwh", received.EnergyValue()));
	return *this;
}

void Notification_EnergyUsage::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	Notification_PublishPayload::Notify(signal);
}

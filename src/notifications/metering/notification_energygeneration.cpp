#include "notifications/metering/notification_energygeneration.h"

const std::string  Notification_EnergyGeneration::MAPKEY_INSTANTANEOUSDEMAND{ "instantaneous_watts" };
const std::string  Notification_EnergyGeneration::MAPKEY_DAILYPRODUCTION{ "daily_production" };
const std::string  Notification_EnergyGeneration::MAPKEY_ANNUALPRODUCTION{ "annual_production" };
const std::string  Notification_EnergyGeneration::MAPKEY_ALLTIMEPRODUCTION{ "alltime_production" };

Notification_EnergyGeneration::Notification_EnergyGeneration(SymoNotification_PublishPayload::Types::DeviceId device_id) :
	SymoNotification_PublishPayload(device_id)
{
}

Notification_EnergyGeneration& Notification_EnergyGeneration::InstantaneousDemand(const Power& now)
{
	m_ElementsMap.insert_or_assign(MAPKEY_INSTANTANEOUSDEMAND, now.ValueIn<Watts>());
	return *this;
}

Notification_EnergyGeneration& Notification_EnergyGeneration::DailyProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DAILYPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_EnergyGeneration& Notification_EnergyGeneration::AnnualProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ANNUALPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_EnergyGeneration& Notification_EnergyGeneration::AllTimeProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ALLTIMEPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

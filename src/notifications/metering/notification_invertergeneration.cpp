#include "notifications/metering/notification_invertergeneration.h"

const std::string Notification_InverterGeneration::MAPKEY_INSTANTANEOUSDEMAND{ "instantaneous_watts" };
const std::string Notification_InverterGeneration::MAPKEY_DAILYPRODUCTION{ "daily_production" };
const std::string Notification_InverterGeneration::MAPKEY_ANNUALPRODUCTION{ "annual_production" };
const std::string Notification_InverterGeneration::MAPKEY_ALLTIMEPRODUCTION{ "alltime_production" };

Notification_InverterGeneration::Notification_InverterGeneration(SymoNotification_PublishPayload::Types::DeviceId device_id) :
	SymoNotification_PublishPayload(device_id)
{
}

Notification_InverterGeneration& Notification_InverterGeneration::InstantaneousDemand(const Power& now)
{
	m_ElementsMap.insert_or_assign(MAPKEY_INSTANTANEOUSDEMAND, now.ValueIn<Watts>());
	return *this;
}

Notification_InverterGeneration& Notification_InverterGeneration::DailyProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DAILYPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_InverterGeneration& Notification_InverterGeneration::AnnualProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ANNUALPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_InverterGeneration& Notification_InverterGeneration::AllTimeProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ALLTIMEPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

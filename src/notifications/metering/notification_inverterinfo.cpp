#include "notifications/metering/notification_inverterinfo.h"

const std::string  Notification_InverterInfo::MAPKEY_INSTANTANEOUSDEMAND{ "instantaneous_watts" };
const std::string  Notification_InverterInfo::MAPKEY_DAILYPRODUCTION{ "daily_production" };
const std::string  Notification_InverterInfo::MAPKEY_ANNUALPRODUCTION{ "annual_production" };
const std::string  Notification_InverterInfo::MAPKEY_ALLTIMEPRODUCTION{ "alltime_production" };

Notification_InverterInfo::Notification_InverterInfo(SymoNotification_PublishPayload::Types::DeviceId device_id) :
	SymoNotification_PublishPayload(device_id)
{
}

Notification_InverterInfo& Notification_InverterInfo::InstantaneousDemand(const Power& now)
{
	m_ElementsMap.insert_or_assign(MAPKEY_INSTANTANEOUSDEMAND, now.ValueIn<Watts>());
	return *this;
}

Notification_InverterInfo& Notification_InverterInfo::DailyProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DAILYPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_InverterInfo& Notification_InverterInfo::AnnualProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ANNUALPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

Notification_InverterInfo& Notification_InverterInfo::AllTimeProduction(const Production& production)
{
	m_ElementsMap.insert_or_assign(MAPKEY_ALLTIMEPRODUCTION, production.ValueIn<KilowattHours>());
	return *this;
}

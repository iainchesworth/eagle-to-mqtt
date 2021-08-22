#ifndef NOTIFICATION_ENERGYGENERATION
#define NOTIFICATION_ENERGYGENERATION

#include <boost/signals2/signal.hpp>

#include "metering/common/energy_value.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_EnergyGeneration : public SymoNotification_PublishPayload
{
	static const std::string MAPKEY_INSTANTANEOUSDEMAND;
	static const std::string MAPKEY_DAILYPRODUCTION;
	static const std::string MAPKEY_ANNUALPRODUCTION;
	static const std::string MAPKEY_ALLTIMEPRODUCTION;

public:
	Notification_EnergyGeneration(SymoNotification_PublishPayload::Types::DeviceId device_id);

public:
	Notification_EnergyGeneration& InstantaneousDemand(const Power& now);
	Notification_EnergyGeneration& DailyProduction(const Production& production);
	Notification_EnergyGeneration& AnnualProduction(const Production& production);
	Notification_EnergyGeneration& AllTimeProduction(const Production& production);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_ENERGYGENERATION

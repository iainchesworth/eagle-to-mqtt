#ifndef NOTIFICATION_INVERTERGENERATION_H
#define NOTIFICATION_INVERTERGENERATION_H

#include <boost/signals2/signal.hpp>

#include <string> 

#include "metering/common/energy_value.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_InverterGeneration : public SymoNotification_PublishPayload
{
	static const std::string MAPKEY_INSTANTANEOUSDEMAND;
	static const std::string MAPKEY_DAILYPRODUCTION;
	static const std::string MAPKEY_ANNUALPRODUCTION;
	static const std::string MAPKEY_ALLTIMEPRODUCTION;

public:
	Notification_InverterGeneration(SymoNotification_PublishPayload::Types::DeviceId device_id);

public:
	Notification_InverterGeneration& InstantaneousDemand(const Power& now);
	Notification_InverterGeneration& DailyProduction(const Production& production);
	Notification_InverterGeneration& AnnualProduction(const Production& production);
	Notification_InverterGeneration& AllTimeProduction(const Production& production);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_INVERTERGENERATION_H

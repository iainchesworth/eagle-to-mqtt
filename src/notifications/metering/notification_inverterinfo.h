#ifndef NOTIFICATION_INVERTERINFO_H
#define NOTIFICATION_INVERTERINFO_H

#include <boost/signals2/signal.hpp>

#include <string> 

#include "metering/common/energy_value.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_InverterInfo : public SymoNotification_PublishPayload
{
	static const std::string MAPKEY_INSTANTANEOUSDEMAND;
	static const std::string MAPKEY_DAILYPRODUCTION;
	static const std::string MAPKEY_ANNUALPRODUCTION;
	static const std::string MAPKEY_ALLTIMEPRODUCTION;

public:
	Notification_InverterInfo(SymoNotification_PublishPayload::Types::DeviceId device_id);

public:
	Notification_InverterInfo& InstantaneousDemand(const Power& now);
	Notification_InverterInfo& DailyProduction(const Production& production);
	Notification_InverterInfo& AnnualProduction(const Production& production);
	Notification_InverterInfo& AllTimeProduction(const Production& production);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_INVERTERINFO_H

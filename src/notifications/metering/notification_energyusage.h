#ifndef NOTIFICATION_ENERGYUSAGE_H
#define NOTIFICATION_ENERGYUSAGE_H

#include <boost/signals2/signal.hpp>

#include "metering/common/energy_value.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_EnergyUsage : public Notification_PublishPayload
{
	static const std::string MAPKEY_INSTANTANEOUSDEMAND;
	static const std::string MAPKEY_LIFETIMEDELIVERED;
	static const std::string MAPKEY_LIFETIMERECEIVED;

public:
	explicit Notification_EnergyUsage(EthernetMacId device_id);

public:
	Notification_EnergyUsage& InstantaneousDemand(const Power& now);
	Notification_EnergyUsage& LifetimeDelivered(const Usage& delivered);
	Notification_EnergyUsage& LifetimeReceived(const Usage& received);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_ENERGYUSAGE_H

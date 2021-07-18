#ifndef NOTIFICATION_ENERGYUSAGE_H
#define NOTIFICATION_ENERGYUSAGE_H

#include <boost/signals2/signal.hpp>

#include "metering/devices/rainforest/messages/partial_message_types/demand.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/devices/rainforest/messages/partial_message_types/summation.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_EnergyUsage : public Notification_PublishPayload
{
public:
	Notification_EnergyUsage(EthernetMacId device_id);

public:
	Notification_EnergyUsage& InstantaneousDemand(const Demand& now);
	Notification_EnergyUsage& LifetimeDelivered(const Summation& delivered);
	Notification_EnergyUsage& LifetimeReceived(const Summation& received);

protected:
	virtual void Notify(boost::signals2::signal<NotificationCallback>& signal);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_ENERGYUSAGE_H

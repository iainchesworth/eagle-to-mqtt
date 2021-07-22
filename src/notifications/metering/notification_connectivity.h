#ifndef NOTIFICATION_CONNECTIVITY_H
#define NOTIFICATION_CONNECTIVITY_H

#include <boost/signals2/signal.hpp>

#include <cstdint>
#include <string>

#include "metering/common/statuses.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_Connectivity : public Notification_PublishPayload
{
	static const std::string MAPKEY_METERMACID;
	static const std::string MAPKEY_EXTENDEDPANID;
	static const std::string MAPKEY_STATUS;
	static const std::string MAPKEY_CHANNEL;
	static const std::string MAPKEY_LINKSTRENGTH;

public:
	explicit Notification_Connectivity(EthernetMacId device_id);

public:
	Notification_Connectivity& Meter_MacId(const ZigBeeMacId& meter_macid);
	Notification_Connectivity& Extended_PanId(const ZigBeeMacId& extended_panid);
	Notification_Connectivity& Status(const Statuses& status);
	Notification_Connectivity& Channel(const std::string& channel);
	Notification_Connectivity& LinkStrength(const uint8_t link_strength);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_CONNECTIVITY_H

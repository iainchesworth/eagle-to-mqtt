#include "notifications/metering/notification_connectivity.h"

const std::string Notification_Connectivity::MAPKEY_METERMACID{ "meter_macid" };
const std::string Notification_Connectivity::MAPKEY_EXTENDEDPANID{ "extended_panid" };
const std::string Notification_Connectivity::MAPKEY_STATUS{ "status" };
const std::string Notification_Connectivity::MAPKEY_CHANNEL{ "channel" };
const std::string Notification_Connectivity::MAPKEY_LINKSTRENGTH{ "link_strength" };

Notification_Connectivity::Notification_Connectivity(EagleNotification_PublishPayload::Types::DeviceId device_id) :
	EagleNotification_PublishPayload(device_id)
{
}

Notification_Connectivity& Notification_Connectivity::Meter_MacId(const ZigBeeMacId& meter_macid)
{
	m_ElementsMap.insert_or_assign(MAPKEY_METERMACID, meter_macid);
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Extended_PanId(const ZigBeeMacId& extended_panid)
{
	m_ElementsMap.insert_or_assign(MAPKEY_EXTENDEDPANID, extended_panid);
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Status(const Statuses& status)
{
	m_ElementsMap.insert_or_assign(MAPKEY_STATUS, status);
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Channel(const std::string& channel)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CHANNEL, channel);
	return *this;
}

Notification_Connectivity& Notification_Connectivity::LinkStrength(const uint8_t link_strength)
{
	m_ElementsMap.insert_or_assign(MAPKEY_LINKSTRENGTH, link_strength);
	return *this;
}

#include "notifications/metering/notification_connectivity.h"

Notification_Connectivity::Notification_Connectivity(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_Connectivity& Notification_Connectivity::Meter_MacId(const ZigBeeMacId& meter_macid)
{
	m_ElementsMap.insert(std::make_pair("meter_macid", meter_macid));
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Extended_PanId(const ZigBeeMacId& extended_panid)
{
	m_ElementsMap.insert(std::make_pair("extended_panid", extended_panid));
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Status(const Statuses& status)
{
	m_ElementsMap.insert(std::make_pair("status", status));
	return *this;
}

Notification_Connectivity& Notification_Connectivity::Channel(const std::string& channel)
{
	m_ElementsMap.insert(std::make_pair("channel", channel));
	return *this;
}

Notification_Connectivity& Notification_Connectivity::LinkStrength(const uint8_t link_strength)
{
	m_ElementsMap.insert(std::make_pair("link_strength", link_strength));
	return *this;
}

void Notification_Connectivity::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	Notification_PublishPayload::Notify(signal);
}

#include "notifications/metering/notification_publishpayload.h"

Notification_PublishPayload::Notification_PublishPayload(MeteringPayload_DeviceId device_id, std::initializer_list<MeteringPayload_Element> payload_elements) :
	NotificationBase(),
	m_ElementsMap(payload_elements),
	m_DeviceId(device_id)
{
}

void Notification_PublishPayload::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	signal(std::make_pair(m_DeviceId, m_ElementsMap));
}

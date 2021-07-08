#ifndef NOTIFICATION_PUBLISHPAYLOAD_H
#define NOTIFICATION_PUBLISHPAYLOAD_H

#include <boost/signals2/signal.hpp>

#include "notifications/notification_base.h"
#include "notifications/common/metering_payload_types.h"

class Notification_PublishPayload : public NotificationBase<void(const MeteringPayload& payload)>
{
public:
	Notification_PublishPayload(MeteringPayload_DeviceId device_id, std::initializer_list<MeteringPayload_Element> payload_elements = {});

protected:
	virtual void Notify(boost::signals2::signal<NotificationCallback>& signal);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;

protected:
	MeteringPayload_ElementMap m_ElementsMap;
	MeteringPayload_DeviceId m_DeviceId;
};

#endif // NOTIFICATION_PUBLISHPAYLOAD_H

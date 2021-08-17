#ifndef NOTIFICATION_SOLARAPI_INVERTER
#define NOTIFICATION_SOLARAPI_INVERTER

#include <boost/signals2/signal.hpp>

#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_SolarApi_Inverter : public SymoNotification_PublishPayload
{
public:
	Notification_SolarApi_Inverter(SymoNotification_PublishPayload::Types::DeviceId device_id);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_SOLARAPI_INVERTER

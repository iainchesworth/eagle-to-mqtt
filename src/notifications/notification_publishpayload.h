#ifndef NOTIFICATION_PUBLISHPAYLOAD_H
#define NOTIFICATION_PUBLISHPAYLOAD_H

#include <boost/signals2/signal.hpp>

#include "notifications/notification_base.h"

class Notification_PublishPayload : public NotificationBase<void()>
{
public:
	Notification_PublishPayload();

protected:
	virtual void Notify(boost::signals2::signal<NotificationCallback>& signal);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_PUBLISHPAYLOAD_H

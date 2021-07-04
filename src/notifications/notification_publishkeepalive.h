#ifndef NOTIFICATION_PUBLISHKEEPALIVE_H
#define NOTIFICATION_PUBLISHKEEPALIVE_H

#include <boost/signals2/signal.hpp>

#include "notifications/notification_base.h"

class Notification_PublishKeepAlive : public NotificationBase<void()>
{
public:
	Notification_PublishKeepAlive();

protected:
	virtual void Notify(boost::signals2::signal<NotificationCallback>& signal);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_PUBLISHKEEPALIVE_H

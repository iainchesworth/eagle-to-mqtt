#include "notifications/notification_publishkeepalive.h"

Notification_PublishKeepAlive::Notification_PublishKeepAlive()
{
}

void Notification_PublishKeepAlive::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	signal();
}

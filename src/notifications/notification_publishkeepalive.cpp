#include "notifications/notification_publishkeepalive.h"

Notification_PublishKeepAlive::Notification_PublishKeepAlive(const std::chrono::seconds uptime) :
	NotificationBase(),
	m_Uptime(uptime)
{
}

void Notification_PublishKeepAlive::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	signal(m_Uptime);
}

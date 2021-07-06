#include "notifications/notification_bridgestatuschanged.h"

Notification_BridgeStatusChanged::Notification_BridgeStatusChanged(const BridgeStatus status) : 
	NotificationBase(),
	m_Status(status)
{
}

void Notification_BridgeStatusChanged::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	signal(m_Status);
}

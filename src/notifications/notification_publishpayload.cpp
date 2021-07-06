#include "notifications/notification_publishpayload.h"

Notification_PublishPayload::Notification_PublishPayload() :
	NotificationBase()
{
}

void Notification_PublishPayload::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	signal();
}

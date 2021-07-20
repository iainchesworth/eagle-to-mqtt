#ifndef NOTIFICATION_PUBLISHKEEPALIVE_H
#define NOTIFICATION_PUBLISHKEEPALIVE_H

#include <boost/signals2/signal.hpp>

#include <chrono>

#include "notifications/notification_base.h"

class Notification_PublishKeepAlive : public NotificationBase<void(const std::chrono::seconds uptime)>
{
public:
	explicit Notification_PublishKeepAlive(const std::chrono::seconds uptime);

protected:
	void Notify(boost::signals2::signal<NotificationCallback>& signal) override;

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;

private:
	const std::chrono::seconds m_Uptime;
};

#endif // NOTIFICATION_PUBLISHKEEPALIVE_H

#ifndef NOTIFICATION_BRIDGESTATUSCHANGED_H
#define NOTIFICATION_BRIDGESTATUSCHANGED_H

#include <boost/signals2/signal.hpp>

#include "bridge/bridge_status.h"
#include "notifications/notification_base.h"

class Notification_BridgeStatusChanged : public NotificationBase<void(const BridgeStatus status)>
{
public:
	explicit Notification_BridgeStatusChanged(const BridgeStatus status);

protected:
	void Notify(boost::signals2::signal<NotificationCallback>& signal) override;

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;

private:
	const BridgeStatus m_Status;
};

#endif // NOTIFICATION_BRIDGESTATUSCHANGED_H

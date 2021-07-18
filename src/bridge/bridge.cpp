#include <boost/core/ignore_unused.hpp>
#include <boost/log/trivial.hpp>

#include <memory>

#include "bridge/bridge.h"
#include "bridge/bridge_registry.h"
#include "notifications/notification_manager.h"
#include "notifications/bridge/notification_bridgestatuschanged.h"
#include "notifications/bridge/notification_publishkeepalive.h"
#include "serialization/bridge_serializer.h"

Bridge::Bridge(boost::asio::io_context& ioc) :
	IBridge(ioc),
	m_UptimeStart(std::chrono::steady_clock::now()),
	m_KeepAliveTimer(ioc),
	m_Status(BridgeStatus::BridgeStatusTypes::Offline),
	m_Statistics()
{
	BOOST_LOG_TRIVIAL(debug) << L"Initialising the Bridge";

	// NOTE: Use of aliasing constructor here.  As compared with the null deleter
	// approach, this doesn't need to allocate a control block, and is noexcept.

	auto bridge_ptr = std::shared_ptr<Bridge>(std::shared_ptr<Bridge>{}, this);
	BridgeRegistrySingleton()->Add(bridge_ptr);
}

Bridge::~Bridge()
{
}

void Bridge::Run()
{
	m_Status = BridgeStatus::BridgeStatusTypes::Online;
	TriggerBridgeStatusChanged();

	TriggerKeepAlive();
}

void Bridge::Stop()
{
	m_KeepAliveTimer.cancel();

	m_Status = BridgeStatus::BridgeStatusTypes::Offline;
	TriggerBridgeStatusChanged();
}

void Bridge::TriggerBridgeStatusChanged()
{
	auto status_changed = std::make_shared<Notification_BridgeStatusChanged>(m_Status);

	NotificationManagerSingleton()->Dispatch(status_changed);
	NotificationManagerSingleton()->Poll();
}

void Bridge::TriggerKeepAlive()
{
	boost::system::error_code ec;

	if (m_KeepAliveTimer.expires_from_now(KEEPALIVE_DURATION, ec); boost::system::errc::success != ec)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Failed to reset keep-alive timer; error was: " << ec;
	}
	else
	{
		m_KeepAliveTimer.async_wait(
			[this](const boost::system::error_code& ec)
			{
				if (boost::asio::error::operation_aborted == ec)
				{
					BOOST_LOG_TRIVIAL(debug) << L"Keep-alive send was aborted; canceling";
				}
				else
				{
					BOOST_LOG_TRIVIAL(debug) << L"Sending keep-alive notification to all publishers";

					auto keep_alive = std::make_shared<Notification_PublishKeepAlive>(Uptime());

					NotificationManagerSingleton()->Dispatch(keep_alive);
					NotificationManagerSingleton()->Poll();

					TriggerKeepAlive();
				}
			});
	}
}

BridgeStatistics Bridge::Statistics() const
{
	return m_Statistics;
}

std::chrono::seconds Bridge::Uptime() const
{
	auto uptime = (std::chrono::steady_clock::now() - m_UptimeStart);
	return std::chrono::duration_cast<std::chrono::seconds>(uptime);
}

boost::json::object Bridge::Serialize() const
{
	return Bridge_Serializer(*this).Serialize();
}

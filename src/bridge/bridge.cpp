#include <boost/core/ignore_unused.hpp>
#include <boost/log/trivial.hpp>

#include <memory>

#include "bridge/bridge.h"
#include "bridge/bridge_registry.h"
#include "notifications/notification_manager.h"
#include "notifications/notification_publishkeepalive.h"

Bridge::Bridge(boost::asio::io_context& ioc) :
	IBridge(ioc),
	m_UptimeStart(std::chrono::steady_clock::now()),
	m_KeepAliveTimer(ioc),
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
	TriggerKeepAlive();
}

void Bridge::Stop()
{
	m_KeepAliveTimer.cancel();
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

					NotificationManagerSingleton()->Dispatch(std::make_shared<Notification_PublishKeepAlive>());
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

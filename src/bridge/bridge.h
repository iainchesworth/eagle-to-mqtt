#ifndef BRIDGE_H
#define BRIDGE_H

#include <boost/asio.hpp>

#include <chrono>

#include "bridge/bridge_stats.h"
#include "bridge/bridge_status.h"
#include "interfaces/ibridge.h"
#include "interfaces/iserializable.h"

class Bridge : public IBridge, public ISerializable
{
	static constexpr std::chrono::seconds KEEPALIVE_DURATION{ 5 };

public:
	explicit Bridge(boost::asio::io_context& ioc);
	virtual ~Bridge() = default;

public:
	void Run() final;
	void Stop() final;

private:
	void TriggerBridgeStatusChanged();
	void TriggerKeepAlive();

public:
	BridgeStatistics Statistics() const;
	std::chrono::seconds Uptime() const;

private:
	const std::chrono::time_point<std::chrono::steady_clock> m_UptimeStart{ std::chrono::steady_clock::now() };
	boost::asio::steady_timer m_KeepAliveTimer;
	BridgeStatus m_Status{ BridgeStatus::BridgeStatusTypes::Offline };
	BridgeStatistics m_Statistics;

public:
	boost::json::object Serialize() const final;
};

#endif // BRIDGE_H

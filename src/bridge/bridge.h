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
	Bridge(boost::asio::io_context& ioc);
	virtual ~Bridge();

public:
	virtual void Run() final;
	virtual void Stop() final;

private:
	void TriggerBridgeStatusChanged();
	void TriggerKeepAlive();

public:
	BridgeStatistics Statistics() const;
	std::chrono::seconds Uptime() const;

private:
	const std::chrono::time_point<std::chrono::steady_clock> m_UptimeStart;	
	boost::asio::steady_timer m_KeepAliveTimer;
	BridgeStatus m_Status;
	BridgeStatistics m_Statistics;

public:
	virtual boost::json::object Serialize() const;
};

#endif // BRIDGE_H

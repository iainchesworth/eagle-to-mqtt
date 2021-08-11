#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

#include <boost/asio.hpp>
#include <mqtt/async_client.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "bridge/bridge_status.h"
#include "notifications/common/metering_payload_types.h"
#include "options/options.h"

class MqttConnection : public std::enable_shared_from_this<MqttConnection>, public mqtt::callback
{
	static const uint32_t MAXIMUM_RETRY_ATTEMPTS{ 2 };

public:
	MqttConnection(boost::asio::io_context& ioc, const Options& options, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr);

public:
	void Start();
	void Stop();

private:
	void NotificationHandler_PublishPayload(const std::string& topic_prefix, const MeteringPayload& metering_payload);
	void NotificationHandler_BridgeStatusChange(const BridgeStatus& bridge_status);
	void NotificationHandler_Connectivity(const MeteringPayload& metering_payload);
	void NotificationHandler_DeviceInfo(const MeteringPayload& metering_payload);
	void NotificationHandler_DeviceStats(const MeteringPayload& metering_payload);
	void NotificationHandler_PublishKeepAlive(const std::chrono::seconds& uptime);
	void NotificationHandler_EnergyUsage(const MeteringPayload& metering_payload);

private:
	void Connect();
	void Publish(const mqtt::message_ptr& message_to_send);
	void RetryConnect();

private:
	void connected(const std::string& cause) override;
	void connection_lost(const std::string& cause) override;
	void delivery_complete(mqtt::delivery_token_ptr tok) override;
	void message_arrived(mqtt::const_message_ptr msg) override;

private:
	void disconnected(const mqtt::properties& properties, mqtt::ReasonCode reason) const;
	bool update_connection_handler(mqtt::connect_data& connect_data) const;

private:
	boost::asio::io_context& m_IOContext;
	const Options& m_Options;

private:
	mqtt::async_client_ptr m_ClientPtr;
	mqtt::connect_options_ptr m_ConnectOptionsPtr;
	uint32_t m_ConnectionRetryAttempt{ 0 };

private:
	using QueuedMessageMap = std::unordered_map<std::type_index, mqtt::message_ptr>;
	QueuedMessageMap m_QueuedSendOnConnect;
	std::mutex m_QueuedSendOnConnectMutex;
};

#endif // MQTT_CONNECTION_H

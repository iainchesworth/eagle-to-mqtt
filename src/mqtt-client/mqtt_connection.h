#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>
#include <mqtt/async_client.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <typeindex>
#include <unordered_map>

#include "bridge/bridge_status.h"
#include "mqtt-client/mqtt-messages/mqtt_message.h"
#include "options/options.h"

class MqttConnection : public std::enable_shared_from_this<MqttConnection>, public virtual mqtt::callback
{
public:
	MqttConnection(boost::asio::io_context& ioc, const Options& options, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr);

public:
	void Start();
	void Stop();

private:
	void NotificationHandler_BridgeStatusChange(const BridgeStatus& bridge_status);
	void NotificationHandler_PublishKeepAlive(const std::chrono::seconds& uptime);
	void NotificationHandler_PublishPayload();

private:
	void Connect();
	void Publish(std::shared_ptr<MqttMessage> message);

public:
	virtual void connected(const std::string& cause) override;
	virtual void connection_lost(const std::string& cause) override;
	void disconnected(const mqtt::properties& properties, mqtt::ReasonCode reason);
	virtual void message_arrived(mqtt::const_message_ptr msg) override;
	virtual void delivery_complete(mqtt::delivery_token_ptr tok) override;

private:
	boost::asio::io_context& m_IOContext;
	const Options& m_Options;

private:
	mqtt::async_client_ptr m_ClientPtr;
	mqtt::connect_options_ptr m_ConnectOptionsPtr;

private:
	using QueuedMessageMap = std::unordered_map<std::type_index, std::shared_ptr<MqttMessage>>;
	QueuedMessageMap m_QueuedSendOnConnect;
	std::mutex m_QueuedSendOnConnectMutex;
};

#endif // MQTT_CONNECTION_H

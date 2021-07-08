#ifndef EAGLE_MQTT_CLIENT_H
#define EAGLE_MQTT_CLIENT_H

#include <boost/asio.hpp>
#include <mqtt/async_client.h>

#include <memory>

#include "interfaces/ipublisher.h"
#include "options/options.h"
#include "mqtt-client/mqtt_connection.h"

class MqttClient : public IPublisher
{
public:
	explicit MqttClient(boost::asio::io_context& ioc, const Options& options);
	virtual ~MqttClient();

public:
	void Run() final;
	void Stop() final;

private:
	std::string MakeClientId() const;
	std::string MakeConnectionString() const;

private:
	const Options& m_Options;

private:
	mqtt::async_client_ptr m_Client;
	mqtt::connect_options_ptr m_ConnectOptions;
	std::shared_ptr<MqttConnection> m_Connection;
	mqtt::message_ptr m_LWT;
};

#endif // EAGLE_MQTT_CLIENT_H

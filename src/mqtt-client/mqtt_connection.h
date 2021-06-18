#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

#include <boost/log/trivial.hpp>
#include <boost/asio.hpp>
#include <mqtt/async_client.h>

#include <memory>
#include <string>

class MqttConnection : public std::enable_shared_from_this<MqttConnection>, public virtual mqtt::callback
{
public:
	MqttConnection(boost::asio::io_context& ioc, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr);

public:
	void Start();
	void Stop();

private:
	void Connect();
	void Publish();

public:
	void connection_lost(const std::string& cause) override;
	void delivery_complete(mqtt::delivery_token_ptr tok) override;

private:
	boost::asio::io_context& m_IOContext;

private:
	mqtt::async_client_ptr m_ClientPtr;
	mqtt::connect_options_ptr m_ConnectOptionsPtr;
};

#endif // MQTT_CONNECTION_H

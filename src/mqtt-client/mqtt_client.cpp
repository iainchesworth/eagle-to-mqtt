#include <spdlog/spdlog.h>

#include "exceptions/not_implemented.h"
#include "mqtt-client/mqtt_client.h"
#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/mqtt_qos.h"

MqttClient::MqttClient(boost::asio::io_context& ioc, const Options& options) :
	IPublisher(ioc),
	m_Options(options),
	m_Client(std::make_shared<mqtt::async_client>(MakeConnectionString(), MakeClientId(), mqtt::create_options(MQTTVERSION_DEFAULT)))
{
	spdlog::info("Starting MQTT client");

	spdlog::debug("Configuring connection to MQTT broker");

	try
	{
		auto options_builder = mqtt::connect_options_builder()
			.automatic_reconnect(std::chrono::milliseconds(100), std::chrono::milliseconds(1000))
			.clean_session()
			.connect_timeout(std::chrono::seconds(60))
			.keep_alive_interval(std::chrono::seconds(10))
			.mqtt_version(MQTTVERSION_DEFAULT);

		if (m_Options.MqttUseTls())
		{
			throw NotImplemented();
		}

		if (m_Options.MqttUseAuthentication())
		{
			options_builder.user_name(m_Options.MqttUsername());
			options_builder.password(m_Options.MqttPassword());
		}

		m_ConnectOptions = std::make_shared<mqtt::connect_options>(options_builder.finalize());
		m_Connection = std::make_shared<MqttConnection>(m_IOContext, m_Options, m_Client, m_ConnectOptions);
	}
	catch (const mqtt::exception& mqtt_ex)
	{
		spdlog::error("Exception occurred while configuring connection to MQTT broker - what(): {}", mqtt_ex.what());
		throw;
	}
}

void MqttClient::Run()
{
	try
	{
		spdlog::debug("Connecting to MQTT broker on {}", m_Client->get_server_uri());
		m_Connection->Start();
	}
	catch (const mqtt::exception& mqtt_ex)
	{
		spdlog::error("Exception occurred while running MQTT Client - what(): {}", mqtt_ex.what());
	}
}

void MqttClient::Stop()
{
	m_Connection->Stop();
}

std::string MqttClient::MakeClientId() const
{
	const std::string DEFAULT_CLIENT_ID{ "eagle-to-mqtt-bridge" };
	return DEFAULT_CLIENT_ID;
}

std::string MqttClient::MakeConnectionString() const
{
	std::string connection_string;
	
	if (m_Options.MqttUseTls())
	{
		connection_string.append("ssl://");
	}
	else
	{
		connection_string.append("tcp://");
	}

	connection_string.append(m_Options.MqttHost());
	connection_string.append(":");
	connection_string.append(std::to_string(m_Options.MqttPort()));

	return connection_string;
}

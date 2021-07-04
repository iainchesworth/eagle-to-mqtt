#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/action-listeners/connect_action_listener.h"
#include "mqtt-client/mqtt-messages/mqtt_bridgekeepalive.h"
#include "notifications/notification_manager.h"
#include "notifications/notification_publishkeepalive.h"
#include "notifications/notification_publishpayload.h"

MqttConnection::MqttConnection(boost::asio::io_context& ioc, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr) :
	m_IOContext(ioc),
	m_ClientPtr(client_ptr),
	m_ConnectOptionsPtr(connect_options_ptr)
{
	NotificationManagerSingleton()->RegisterCallback<Notification_PublishPayload>(
		[this]() 
		{
			BOOST_LOG_TRIVIAL(debug) << L"Notification_PayloadToPublish() -> Notification received by MQTT Connection";

			if (m_ClientPtr->is_connected())
			{
				///TODO
			}
		});

	NotificationManagerSingleton()->RegisterCallback<Notification_PublishKeepAlive>(
		[this]()
		{
			BOOST_LOG_TRIVIAL(debug) << L"Notification_PublishKeepAlive() -> Notification received by MQTT Connection";
			
			if (m_ClientPtr->is_connected())
			{
				Publish(std::make_unique<Mqtt_BridgeKeepAlive>());
			}
		});
}

void MqttConnection::Start()
{
	Connect();
}

void MqttConnection::Stop()
{
	if (m_ClientPtr->is_connected())
	{
		m_ClientPtr->disconnect();
	}
}

void MqttConnection::Connect()
{
	auto self = shared_from_this();

	m_IOContext.post([self]()
		{
			ConnectActionListener connection_action_listener;

			mqtt::token_ptr conntok = self->m_ClientPtr->connect(*(self->m_ConnectOptionsPtr), nullptr, connection_action_listener);

			BOOST_LOG_TRIVIAL(debug) << L"Waiting for connection to MQTT broker";
			
			conntok->wait();
		});

}

void MqttConnection::Publish(std::unique_ptr<MqttMessage> message)
{
	auto self = shared_from_this();

	m_IOContext.post([self]()
		{
			if (!self->m_ClientPtr->is_connected())
			{
				BOOST_LOG_TRIVIAL(warning) << L"Cannot publish message, client is disconnected";
			}
			else
			{

			}
		});
}

void MqttConnection::connection_lost(const std::string& cause)
{
	BOOST_LOG_TRIVIAL(warning) << L"Connection lost to MQTT broker";

	if (!cause.empty())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Cause of lost connection: " << cause;
	}
}

void MqttConnection::delivery_complete(mqtt::delivery_token_ptr tok)
{
	BOOST_LOG_TRIVIAL(debug) << L"Message successfully delivered to MQTT broker";
}

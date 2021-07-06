#include <functional>

#include "mqtt-client/mqtt_connection.h"
#include "mqtt-client/action-listeners/connect_action_listener.h"
#include "notifications/notification_manager.h"
#include "notifications/bridge/notification_bridgestatuschanged.h"
#include "notifications/bridge/notification_publishkeepalive.h"
#include "notifications/metering/notification_publishpayload.h"

MqttConnection::MqttConnection(boost::asio::io_context& ioc, const Options& options, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr) :
	m_IOContext(ioc),
	m_Options(options),
	m_ClientPtr(client_ptr),
	m_ConnectOptionsPtr(connect_options_ptr),
	m_QueuedSendOnConnect{},
	m_QueuedSendOnConnectMutex()
{
	///

	m_ClientPtr->set_connected_handler(std::bind(&MqttConnection::connected, this, std::placeholders::_1));
	m_ClientPtr->set_connection_lost_handler(std::bind(&MqttConnection::connection_lost, this, std::placeholders::_1));
	m_ClientPtr->set_disconnected_handler(std::bind(&MqttConnection::disconnected, this, std::placeholders::_1, std::placeholders::_2));

	///

	NotificationManagerSingleton()->RegisterCallback<Notification_BridgeStatusChanged>(std::bind(&MqttConnection::NotificationHandler_BridgeStatusChange, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_PublishKeepAlive>(std::bind(&MqttConnection::NotificationHandler_PublishKeepAlive, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_PublishPayload>(std::bind(&MqttConnection::NotificationHandler_PublishPayload, this));
}

void MqttConnection::Start()
{
	Connect();
}

void MqttConnection::Stop()
{
	if (m_ClientPtr->is_connected())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Disconnecting MQTT client from broker";
		m_ClientPtr->disconnect();
	}
}

void MqttConnection::Connect()
{
	auto self = shared_from_this();

	m_IOContext.post([self]()
		{
			mqtt::token_ptr conntok = self->m_ClientPtr->connect(*(self->m_ConnectOptionsPtr));

			BOOST_LOG_TRIVIAL(debug) << L"Waiting for connection to MQTT broker";

			conntok->wait();
		});

}

void MqttConnection::Publish(std::shared_ptr<MqttMessage> message_to_send)
{
	auto self = shared_from_this();

	m_IOContext.post([self, message_to_send]()
		{
			if (!self->m_ClientPtr->is_connected())
			{
				BOOST_LOG_TRIVIAL(warning) << L"Cannot publish message, client is disconnected";
			}
			else
			{
				BOOST_LOG_TRIVIAL(trace) << L"Publishing MQTT message";
				self->m_ClientPtr->publish(message_to_send->Message())->wait();
			}
		});
}

void MqttConnection::connected(const std::string& cause)
{
	BOOST_LOG_TRIVIAL(info) << L"Connected to " << m_ClientPtr->get_server_uri();

	std::lock_guard<std::mutex> guard(m_QueuedSendOnConnectMutex);
	
	if (m_QueuedSendOnConnect.empty())
	{
		BOOST_LOG_TRIVIAL(trace) << L"No MQTT messages in the queued send map; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Publishing the set of " << m_QueuedSendOnConnect.size() << L" queued messages";

		std::for_each(m_QueuedSendOnConnect.begin(), m_QueuedSendOnConnect.end(),
			[this](QueuedMessageMap::value_type& queued_message)
			{
				if (auto message_ptr = queued_message.second; nullptr != message_ptr)
				{
					BOOST_LOG_TRIVIAL(trace) << L"Publishing queued message: " << queued_message.first.name();
					Publish(message_ptr);
				}
			});
		m_QueuedSendOnConnect.clear();
	}
}

void MqttConnection::connection_lost(const std::string& cause)
{
	BOOST_LOG_TRIVIAL(warning) << L"Connection lost to MQTT broker";

	if (!cause.empty())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Cause of lost connection: " << cause;
	}
}

void MqttConnection::disconnected(const mqtt::properties& properties, mqtt::ReasonCode reason)
{
	BOOST_LOG_TRIVIAL(debug) << L"Disconnected from MQTT broker; reason: " << reason;
}

void MqttConnection::message_arrived(mqtt::const_message_ptr msg)
{
	BOOST_LOG_TRIVIAL(debug) << L"Message received from MQTT broker";
}

void MqttConnection::delivery_complete(mqtt::delivery_token_ptr tok)
{
	BOOST_LOG_TRIVIAL(debug) << L"Message successfully delivered to MQTT broker";
}

#include <boost/core/ignore_unused.hpp>
#include <spdlog/spdlog.h>

#include <functional>

#include "mqtt-client/mqtt_connection.h"
#include "notifications/notification_manager.h"
#include "notifications/bridge/notification_bridgestatuschanged.h"
#include "notifications/bridge/notification_publishkeepalive.h"
#include "notifications/metering/notification_connectivity.h"
#include "notifications/metering/notification_deviceinfo.h"
#include "notifications/metering/notification_devicestats.h"
#include "notifications/metering/notification_energygeneration.h"
#include "notifications/metering/notification_energyusage.h"

MqttConnection::MqttConnection(boost::asio::io_context& ioc, const Options& options, mqtt::async_client_ptr client_ptr, mqtt::connect_options_ptr connect_options_ptr) :
	m_IOContext(ioc),
	m_Options(options),
	m_ClientPtr(client_ptr),
	m_ConnectOptionsPtr(connect_options_ptr)
{
	///

	m_ClientPtr->set_callback(*this);
	m_ClientPtr->set_disconnected_handler(std::bind(&MqttConnection::disconnected, this, std::placeholders::_1, std::placeholders::_2));
	m_ClientPtr->set_update_connection_handler(std::bind(&MqttConnection::update_connection_handler, this, std::placeholders::_1));

	///

	NotificationManagerSingleton()->RegisterCallback<Notification_BridgeStatusChanged>(std::bind(&MqttConnection::NotificationHandler_BridgeStatusChange, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_Connectivity>(std::bind(&MqttConnection::NotificationHandler_Connectivity, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_DeviceInfo>(std::bind(&MqttConnection::NotificationHandler_DeviceInfo, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_DeviceStats>(std::bind(&MqttConnection::NotificationHandler_DeviceStats, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_EnergyUsage>(std::bind(&MqttConnection::NotificationHandler_EnergyUsage, this, std::placeholders::_1));
	NotificationManagerSingleton()->RegisterCallback<Notification_PublishKeepAlive>(std::bind(&MqttConnection::NotificationHandler_PublishKeepAlive, this, std::placeholders::_1));

	///
	NotificationManagerSingleton()->RegisterCallback<Notification_EnergyGeneration>(std::bind(&MqttConnection::NotifcationHandler_EnergyGeneration, this, std::placeholders::_1));
}

void MqttConnection::Start()
{
	Connect();
}

void MqttConnection::Stop()
{
	if (m_ClientPtr->is_connected())
	{
		spdlog::debug("Disconnecting MQTT client from broker");
		m_ClientPtr->disconnect();
	}
}

void MqttConnection::Connect()
{
	auto self = shared_from_this();

	m_IOContext.post([self]()
		{
			try
			{
				mqtt::token_ptr conntok = self->m_ClientPtr->connect(*(self->m_ConnectOptionsPtr));

				spdlog::debug("Waiting for connection to MQTT broker");

				conntok->wait();
			}
			catch (const mqtt::security_exception& mqtt_secex)
			{
				spdlog::warn("Security exception while connecting to MQTT broker - code: {}; message: {}", mqtt_secex.get_reason_code(), mqtt_secex.get_message());
			}
			catch (const mqtt::exception& mqtt_ex)
			{
				spdlog::info("Exception while connecting to MQTT broker - code: {}; message: {}", mqtt_ex.get_reason_code(), mqtt_ex.get_message());
				
				self->RetryConnect();
			}
		});

}

void MqttConnection::Publish(const mqtt::message_ptr& message_to_send)
{
	auto self = shared_from_this();

	m_IOContext.post([self, message_to_send]()
		{
			try 
			{
				if (!self->m_ClientPtr->is_connected())
				{
					spdlog::warn("Cannot publish message, client is disconnected");
				}
				else
				{
					spdlog::trace("Publishing MQTT message");
					self->m_ClientPtr->publish(message_to_send)->wait();
				}
			}
			catch (const mqtt::security_exception& mqtt_secex)
			{
				spdlog::warn("Security exception while publishing to MQTT broker - code: {}; message: {}", mqtt_secex.get_reason_code(), mqtt_secex.get_message());
			}
			catch (const mqtt::exception& mqtt_ex)
			{
				spdlog::info("Exception while connecting to MQTT broker - code: {}; message: {}", mqtt_ex.get_reason_code(), mqtt_ex.get_message());
			}
		});
}

void MqttConnection::RetryConnect()
{
	if (MAXIMUM_RETRY_ATTEMPTS >= m_ConnectionRetryAttempt)
	{
		++m_ConnectionRetryAttempt;

		spdlog::info("Reconnecting to MQTT broker: attempt {}", m_ConnectionRetryAttempt);

		Connect();
	}
	else
	{
		spdlog::warn("Failed to reconnect to MQTT broker");
	}
}

void MqttConnection::connected(const std::string& cause)
{
	spdlog::info("Connected to {}", m_ClientPtr->get_server_uri());

	// Reset the connection attempts counter (in case of disconnection).
	m_ConnectionRetryAttempt = 0;

	std::scoped_lock guard(m_QueuedSendOnConnectMutex);
	if (m_QueuedSendOnConnect.empty())
	{
		spdlog::trace("No MQTT messages in the queued send map; ignoring");
	}
	else
	{
		spdlog::debug("Publishing the set of {} queued messages", m_QueuedSendOnConnect.size());

		std::for_each(m_QueuedSendOnConnect.begin(), m_QueuedSendOnConnect.end(),
			[this](const QueuedMessageMap::value_type& queued_message)
			{
				if (auto message_ptr = queued_message.second; nullptr != message_ptr)
				{
					spdlog::trace("Publishing queued message: {}", queued_message.first.name());
					Publish(message_ptr);
				}
			});
		m_QueuedSendOnConnect.clear();
	}
}

void MqttConnection::connection_lost(const std::string& cause)
{
	spdlog::warn("Connection lost to MQTT broker");

	if (!cause.empty())
	{
		spdlog::debug("Cause of lost connection: {}", cause);
	}

	RetryConnect();
}

void MqttConnection::message_arrived(mqtt::const_message_ptr msg)
{
	boost::ignore_unused(msg);

	spdlog::debug("Message received from MQTT broker");
}

void MqttConnection::delivery_complete(mqtt::delivery_token_ptr tok)
{
	boost::ignore_unused(tok);

	spdlog::debug("Message successfully delivered to MQTT broker");
}

void MqttConnection::disconnected(const mqtt::properties& properties, mqtt::ReasonCode reason) const
{
	boost::ignore_unused(properties);

	spdlog::debug("Disconnected from MQTT broker; reason: {}", reason);
}

bool MqttConnection::update_connection_handler(mqtt::connect_data& connect_data) const
{
	boost::ignore_unused(connect_data);
	
	return true;
}

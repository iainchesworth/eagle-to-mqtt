#include <boost/log/trivial.hpp>

#include "mqtt-client/action-listeners/connect_action_listener.h"

void ConnectActionListener::on_failure(const mqtt::token& tok)
{
	BOOST_LOG_TRIVIAL(error) << L"Failed to connect to MQTT broker";
}

void ConnectActionListener::on_success(const mqtt::token& tok)
{
	BOOST_LOG_TRIVIAL(info) << L"Connected to " << tok.get_connect_response().get_server_uri();
}

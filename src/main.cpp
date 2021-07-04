#include <boost/asio/io_context.hpp>
#include <boost/log/trivial.hpp>

#include <exception>

#include "application/application.h"
#include "bridge/bridge.h"
#include "options/options.h"
#include "mqtt-client/mqtt_client.h"
#include "upload-api/upload_api.h"

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context ioc{ 1 };

		Options options(argc, argv);

		ListenerSet listeners;
		PublisherSet publishers;

		listeners.push_back(std::make_shared<UploaderAPI>(ioc, options));
		publishers.push_back(std::make_shared<MqttClient>(ioc, options));

		Bridge bridge(ioc);
		
		Application app(ioc, options, bridge, std::move(listeners), std::move(publishers));

		BOOST_LOG_TRIVIAL(info) << L"EAGLE-TO-MQTT - Application Starting";

		app.Run();
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(fatal) << ex.what() << std::endl;
		return -1;
	}

	return 0;
}

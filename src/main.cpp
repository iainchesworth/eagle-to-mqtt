#include <boost/asio/io_context.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include <exception>
#include <memory>

#include "application/application.h"
#include "bridge/bridge.h"
#include "options/options.h"
#include "mqtt-client/mqtt_client.h"
#include "upload-api/http_router.h"
#include "upload-api/routes/root.h"
#include "upload-api/routes/status.h"
#include "upload-api/routes/update-fronius.h"
#include "upload-api/routes/update-rainforest.h"
#include "upload-api/upload_api.h"

int main(int argc, char* argv[])
{
	try
	{
		boost::asio::io_context ioc{ 1 };

		const Options options(argc, argv);

		HttpRouter http_router;
		http_router.AddRoute(std::make_shared<ApiRoute_Root>());

		if (options.StatisticsReportingIsEnabled())
		{
			auto route_status = std::make_shared<ApiRoute_Status>();
			spdlog::debug("Enabling API route: {}", *route_status);
			http_router.AddRoute(route_status);
		}

		if (options.FroniusIntegrationIsEnabled())
		{
			auto route_fronius = std::make_shared<ApiRoute_Fronius>();
			spdlog::debug("Enabling API route: {}", *route_fronius);
			http_router.AddRoute(route_fronius);
		}

		if (options.RainforestIntegrationIsEnabled())
		{
			auto route_rainforest = std::make_shared<ApiRoute_Rainforest>();
			spdlog::debug("Enabling API route: {}", *route_rainforest);
			http_router.AddRoute(route_rainforest);
		}

		Bridge bridge(ioc);
		ListenerSet listeners{ std::make_shared<UploaderAPI>(ioc, options, http_router) };
		PublisherSet publishers{ std::make_shared<MqttClient>(ioc, options) };
		
		Application app(ioc, options, bridge, std::move(listeners), std::move(publishers));

		spdlog::info("EAGLE-TO-MQTT - Application Starting");

		app.Run();
	}
	catch (const std::exception& ex)
	{
		spdlog::critical(ex.what());
		return -1;
	}

	return 0;
}

#include <boost/log/trivial.hpp>
#include <boost/json.hpp>

#include "bridge/bridge_registry.h"
#include "metering/device_registry.h"
#include "serialization/bridge_serializer.h"
#include "upload-api/responses/response_200.h"
#include "upload-api/routes/status.h"

const std::string ApiRoute_Status::APIROUTE_REGEX{ "^/status[/]??$" };

ApiRoute_Status::ApiRoute_Status() :
	IApiRoute(boost::beast::http::verb::get, APIROUTE_REGEX)
{
}

HttpResponse ApiRoute_Status::Handler(const HttpRequest& request)
{
    boost::json::object response_object;
	std::stringstream response_stream;
    
	// Report the bridge information
	auto bridge = BridgeRegistrySingleton()->operator()();
	if (nullptr == bridge)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Cannot serialize bridge - object is not initialized in registry";
	}
	else
	{
		response_object["bridge"] = Bridge_Serializer(*bridge).Serialize();
	}

	// Report the collection of Eagle devices
	for (auto device : *DeviceRegistrySingleton())
	{
		if (!device.second)
		{
			BOOST_LOG_TRIVIAL(debug) << L"Cannot serialize device - object is not initialized in registry";
		}
		else
		{
            BOOST_LOG_TRIVIAL(debug) << L"Serialising device object";
			response_object[EthernetMacId::ToString(device.first)] = device.second->Serialize();
		}
	}

    const auto test_string = boost::json::serialize(response_object);
	return make_200<boost::beast::http::string_body>(request, boost::json::serialize(response_object), "application/json");
}

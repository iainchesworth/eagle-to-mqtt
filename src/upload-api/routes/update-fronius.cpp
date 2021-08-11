#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include <memory>
#include <sstream>

#include "metering/device_identifier.h"
#include "metering/devices/fronius/symo.h"
#include "upload-api/responses/response_200.h"
#include "upload-api/responses/response_400.h"
#include "upload-api/routes/update-fronius.h"

namespace pt = boost::property_tree;

const std::string ApiRoute_Fronius::APIROUTE_REGEX{ "^/upload/fronius[/]??$" };

ApiRoute_Fronius::ApiRoute_Fronius() :
	IApiRoute(boost::beast::http::verb::post, APIROUTE_REGEX)
{
}

HttpResponse ApiRoute_Fronius::Handler(const HttpRequest& request)
{
	spdlog::trace("Received Update (Fronius) Payload: \n{}", boost::beast::make_printable(request.body().data()));

	std::istringstream iss(boost::beast::buffers_to_string(request.body().data()));

	pt::ptree upload_dataset;
	pt::read_json(iss, upload_dataset);

	try
	{
		std::shared_ptr<IDevice> symo_processor(IdentifyAndGetSymoInstance(upload_dataset));
		if (nullptr == symo_processor)
		{
			spdlog::warn("Failed to determine the specific device type reporting data!");
		}
		else
		{
			symo_processor->ProcessPayload(upload_dataset);
		}
	}
	catch (const pt::ptree_error& pte)
	{
		spdlog::warn("Failed to parse XML in upload payload; exception was: {}", pte.what());
		return make_400<boost::beast::http::string_body>(request, "Cannot find top-level upload data element; payload is malformed", "text/html");
	}

	return make_200<boost::beast::http::string_body>(request, "", "text/html");
}

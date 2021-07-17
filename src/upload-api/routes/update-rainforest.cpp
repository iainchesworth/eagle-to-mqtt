#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <memory>
#include <sstream>
#include <string>

#include "exceptions/unknown_fragment_type.h"
#include "metering/device_identifier.h"
#include "metering/devices/rainforest/eagle.h"
#include "upload-api/responses/response_200.h"
#include "upload-api/responses/response_400.h"
#include "upload-api/responses/response_500.h"
#include "upload-api/routes/update-rainforest.h"

namespace pt = boost::property_tree;

boost::beast::http::response<boost::beast::http::string_body> Update_Rainforest(const boost::beast::http::request<boost::beast::http::dynamic_body>& req)
{
	BOOST_LOG_TRIVIAL(trace) << L"Received Update (Rainforest) Payload: " << std::endl << boost::beast::make_printable(req.body().data());

	std::istringstream iss(boost::beast::buffers_to_string(req.body().data()));

	pt::ptree upload_dataset;
	pt::read_xml(iss, upload_dataset);

	try
	{
		std::shared_ptr<IDevice> eagle_processor(IdentifyAndGetEagleInstance(upload_dataset));
		if (nullptr == eagle_processor)
		{
			BOOST_LOG_TRIVIAL(warning) << L"Failed to determine the specific device type reporting data!";
		}
		else
		{
			eagle_processor->ProcessPayload(upload_dataset);
		}
	}
	catch (const UnknownFragmentType& ufte)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Failed to match fragment type to known value - fragment: " << ufte.Fragment();

		// If the requested path ("rainforest") cannot be resolved, get_child throws...
		return make_500<boost::beast::http::string_body>(req, "Error while processing XML fragments: unknown fragment type", "text/html");
	}
	catch (const pt::ptree_error& pte)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Failed to parse XML in upload payload; exception was: " << pte.what();

		// If the requested path ("rainforest") cannot be resolved, get_child throws...
		return make_400<boost::beast::http::string_body>(req, "Cannot find top-level upload data element; payload is malformed", "text/html");
	}

	return make_200<boost::beast::http::string_body>(req, "", "text/html");;
}
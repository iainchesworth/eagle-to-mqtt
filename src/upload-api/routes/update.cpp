#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <memory>
#include <sstream>
#include <string>

#include "exceptions/unknown_fragment_type.h"
#include "interfaces/ieagle.h"
#include "metering/eagle-200/eagle_200.h"
#include "metering/rfa-z109/rfa_z109.h"
#include "upload-api/responses/response_200.h"
#include "upload-api/responses/response_400.h"
#include "upload-api/responses/response_500.h"
#include "upload-api/routes/update.h"

namespace pt = boost::property_tree;

boost::beast::http::response<boost::beast::http::string_body> Update(const boost::beast::http::request<boost::beast::http::dynamic_body>& req)
{
	BOOST_LOG_TRIVIAL(trace) << L"Received Update Payload: " << std::endl << boost::beast::make_printable(req.body().data());

	std::istringstream iss(boost::beast::buffers_to_string(req.body().data()));

	pt::ptree upload_dataset;
	pt::read_xml(iss, upload_dataset);

	try
	{
		std::shared_ptr<IEagle> eagle_processor;

		boost::optional<std::string> processor_v1; // <sigh> ... yes, the v1 version string is "undefined" (see RFA-Z109 v6 doco)
		boost::optional<double> processor_v2;

		const auto rainforest_child = upload_dataset.get_child_optional("rainforest");
		if (!rainforest_child)
		{
			BOOST_LOG_TRIVIAL(warning) << L"No version present in the payload; halting processing!";
		}
		else if (processor_v1 = rainforest_child.get().get_optional<std::string>("<xmlattr>.version"); processor_v1.is_initialized() && (0 == processor_v1.get().compare("undefined")))
		{
			BOOST_LOG_TRIVIAL(debug) << L"Detected RFA-Z109";
			eagle_processor = std::make_shared<RFA_Z109>();
			eagle_processor->ProcessPayload(upload_dataset);

		}
		else if (processor_v2 = rainforest_child.get().get_optional<double>("<xmlattr>.version"); processor_v2.is_initialized() && (2.0 == processor_v2.get()))
		{
			BOOST_LOG_TRIVIAL(debug) << L"Detected EAGLE-200";
			eagle_processor = std::make_shared<Eagle200>();
			eagle_processor->ProcessPayload(upload_dataset);
		}
		else
		{
			BOOST_LOG_TRIVIAL(warning) << L"Unknown version present in the payload; halting processing";
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

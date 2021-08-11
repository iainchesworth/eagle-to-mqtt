#include <spdlog/spdlog.h>

#include "upload-api/http_router.h"
#include "upload-api/responses/response_400.h"

HttpRouter::HttpRouter() : 
	IHttpRouter()
{
}

HttpRouter& HttpRouter::AddRoute(const std::shared_ptr<IApiRoute> route)
{
	m_Routes.push_back(route);
	return *this;
}

HttpResponse HttpRouter::HandleRoute(const HttpRequest& req) const
{
	auto it = std::find_if(m_Routes.cbegin(), m_Routes.cend(), [&req](auto route)
		{
			bool is_match_1 = std::regex_match(req.target().begin(), req.target().end(), route->UrlPattern());	// Does the URL match the existing route?
			bool is_match_2 = (route->Method() == req.method());												// Does the verb used match the existing route?

			return (is_match_1 && is_match_2);
		});

	HttpResponse res;

	if (m_Routes.end() == it)
	{
		spdlog::warn("Attempted to match an unsupported route: {}", req.target().to_string());
		res = make_400<boost::beast::http::string_body>(req, "Route not supported", "text/html");
	}
	else
	{
		spdlog::debug("Matched {} to existing route handler; handling route", req.target().to_string());
		res = (*it)->Handler(req);
	}

	return res;
}

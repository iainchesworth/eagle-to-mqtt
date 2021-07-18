#include <boost/log/trivial.hpp>

#include "upload-api/http_router.h"
#include "upload-api/responses/response_400.h"

HttpRouter::HttpRouter() : 
	IHttpRouter(),
	m_Routes()
{
}

HttpRouter::~HttpRouter()
{
}

/*void HttpRouter::Get(const std::string& regex, HttpRouteHandler handler)
{
	BOOST_LOG_TRIVIAL(debug) << L"Adding new route: GET " << regex;
	AddRoute(regex, boost::beast::http::verb::get, handler);
}

void HttpRouter::Post(const std::string& regex, HttpRouteHandler handler)
{
	BOOST_LOG_TRIVIAL(debug) << L"Adding new route: POST " << regex;
	AddRoute(regex, boost::beast::http::verb::post, handler);
}*/

HttpRouter& HttpRouter::AddRoute(const std::shared_ptr<IApiRoute> route)
{
	m_Routes.push_back(route);
	return *this;
}

/*void HttpRouter::AddRoute(const std::string& regex, boost::beast::http::verb method, HttpRouteHandler handler)
{
	Route route;

	route.url_regex = std::regex(regex, std::regex::ECMAScript | std::regex::icase | std::regex::optimize);
	route.method = method;
	route.handler = handler;

	m_Routes.push_back(route);
}*/

HttpResponse HttpRouter::HandleRoute(const HttpRequest& req) const
{
	auto it = std::find_if(m_Routes.cbegin(), m_Routes.cend(), [&req](auto route) -> bool
		{
			bool is_match = true;

			is_match &= std::regex_match(req.target().begin(), req.target().end(), route->UrlPattern());	// Does the URL match the existing route?
			is_match &= (route->Method() == req.method());													// Does the verb used match the existing route?

			return is_match;
		});

	HttpResponse res;

	if (m_Routes.end() == it)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Attempted to match an unsupported route: " << req.target();
		res = make_400<boost::beast::http::string_body>(req, "Route not supported", "text/html");
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Matched " << req.target() << L" to existing route handler; handling route";
		res = (*it)->Handler(req);
	}

	return res;
}

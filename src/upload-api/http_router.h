#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#include <boost/beast/http.hpp>

#include <regex>
#include <string>
#include <vector>

#include "upload-api/responses/response_400.h"

class HttpRouter
{
public:
	using HttpRequest = boost::beast::http::request<boost::beast::http::dynamic_body>;
	using HttpResponse = boost::beast::http::response<boost::beast::http::string_body>;
	using HttpRouteHandler = std::function<HttpResponse(const HttpRequest&)>;

	struct Route
	{
		std::regex url_regex;
		boost::beast::http::verb method;
		HttpRouteHandler handler;
	};

public:
	void Get(const std::string& regex, HttpRouteHandler handler);
	void Post(const std::string& regex, HttpRouteHandler handler);

public:
	HttpResponse HandleRoute(HttpRequest& req) const;

private:
	void AddRoute(const std::string& regex, boost::beast::http::verb method, HttpRouteHandler handler);

private:
	std::vector<Route> m_Routes;
};

#endif // HTTP_ROUTER_H

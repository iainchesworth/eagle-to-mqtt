#ifndef IAPIROUTE_H
#define IAPIROUTE_H

#include <boost/beast/http.hpp>

#include <ostream>
#include <regex>
#include <string>

#include "upload-api/http_types.h"

class IApiRoute
{
public:
	IApiRoute(const boost::beast::http::verb& method, const std::string& regex);

public:
	virtual HttpResponse Handler(const HttpRequest& request) = 0;

public:
	boost::beast::http::verb Method() const;
	std::regex UrlPattern() const;

private:
	boost::beast::http::verb m_Method;
	std::string m_RegexPattern;
	std::regex m_UrlRegex;

public:
	friend std::ostream& operator<<(std::ostream& os, const IApiRoute& api_route);
};

#endif // IAPIROUTE_H

#include "interfaces/iapiroute.h"

IApiRoute::IApiRoute(const boost::beast::http::verb& method, const std::string& regex) :
	m_Method(method),
	m_RegexPattern(regex),
	m_UrlRegex(std::regex(regex, std::regex::ECMAScript | std::regex::icase | std::regex::optimize))
{
}

IApiRoute::~IApiRoute()
{
}

boost::beast::http::verb IApiRoute::Method() const
{
	return m_Method;
}

std::regex IApiRoute::UrlPattern() const
{
	return m_UrlRegex;
}

std::ostream& operator<<(std::ostream& os, const IApiRoute& api_route)
{
	os << api_route.m_RegexPattern;
	return os;
}

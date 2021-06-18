#ifndef ROUTEUPDATE_H
#define ROUTEUPDATE_H

#include <boost/beast/http.hpp>

boost::beast::http::response<boost::beast::http::string_body> Update(const boost::beast::http::request<boost::beast::http::dynamic_body>& req);

#endif // ROUTEUPDATE_H

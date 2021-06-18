#ifndef ROUTEROOT_H
#define ROUTEROOT_H

#include <boost/beast/http.hpp>

boost::beast::http::response<boost::beast::http::string_body> Root(const boost::beast::http::request<boost::beast::http::dynamic_body>& req);

#endif // ROUTEROOT_H

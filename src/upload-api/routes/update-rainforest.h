#ifndef ROUTE_UPDATE_EAGLE_H
#define ROUTE_UPDATE_EAGLE_H

#include <boost/beast/http.hpp>

boost::beast::http::response<boost::beast::http::string_body> Update_Rainforest(const boost::beast::http::request<boost::beast::http::dynamic_body>& req);

#endif // ROUTE_UPDATE_EAGLE_H

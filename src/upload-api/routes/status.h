#ifndef ROUTESTATUS_H
#define ROUTESTATUS_H

#include <boost/beast/http.hpp>

boost::beast::http::response<boost::beast::http::string_body> Status(const boost::beast::http::request<boost::beast::http::dynamic_body>& req);

#endif // ROUTESTATUS_H

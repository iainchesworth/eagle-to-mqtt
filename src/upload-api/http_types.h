#ifndef HTTP_TYPES_H
#define HTTP_TYPES_H

#include <boost/beast/http.hpp>

using HttpRequest = boost::beast::http::request<boost::beast::http::dynamic_body>;
using HttpResponse = boost::beast::http::response<boost::beast::http::string_body>;

#endif // HTTP_TYPES_H

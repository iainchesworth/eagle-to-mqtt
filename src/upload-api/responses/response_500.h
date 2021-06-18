#ifndef RESPONSE_500_H
#define RESPONSE_500_H

#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>

template<class ResponseBody, class RequestBody>
auto make_500(const boost::beast::http::request<RequestBody>& request, typename ResponseBody::value_type body, boost::beast::string_view content)
{
    boost::beast::http::response<ResponseBody> response{ boost::beast::http::status::internal_server_error, request.version() };
    response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(boost::beast::http::field::content_type, content);
    response.body() = body;
    response.prepare_payload();
    response.keep_alive(request.keep_alive());

    return response;
}

#endif // RESPONSE_500_H

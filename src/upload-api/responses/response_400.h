#ifndef RESPONSE_400_H
#define RESPONSE_400_H

#include <boost/beast/version.hpp>
#include <boost/beast/http.hpp>

template<class ResponseBody, class RequestBody>
auto make_400(const boost::beast::http::request<RequestBody>& request, typename ResponseBody::value_type body, boost::beast::string_view content)
{
    boost::beast::http::response<ResponseBody> response{ boost::beast::http::status::bad_request, request.version() };
    response.set(boost::beast::http::field::server, BOOST_BEAST_VERSION_STRING);
    response.set(boost::beast::http::field::content_type, content);
    response.body() = body;
    response.prepare_payload();
    response.keep_alive(request.keep_alive());

    return response;
}

#endif // RESPONSE_400_H

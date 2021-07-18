#ifndef HTTP_CONNECTION_H
#define HTTP_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <chrono>
#include <memory>

#include "interfaces/ihttprouter.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
	HttpConnection(boost::asio::ip::tcp::socket socket, const IHttpRouter& api_router);

public:
	void Start();

private:
	void ReadRequest();
	void ProcessRequest();
	void WriteResponse();
	void CheckDeadline();

private:
	boost::asio::ip::tcp::socket m_Socket;
	boost::beast::flat_buffer m_Buffer{ 8192 };
	boost::beast::http::request<boost::beast::http::dynamic_body> m_Request;
	boost::beast::http::response<boost::beast::http::string_body> m_Response;
	boost::asio::steady_timer m_Deadline{ m_Socket.get_executor(), std::chrono::seconds(60) };

private:
	const IHttpRouter& m_ApiRouter;
};

#endif // HTTP_CONNECTION_H

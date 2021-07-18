#include <boost/beast/http.hpp>
#include <boost/log/trivial.hpp>

#include "upload-api/http_connection.h"
#include "upload-api/responses/response_400.h"
#include "upload-api/responses/response_500.h"

HttpConnection::HttpConnection(boost::asio::ip::tcp::socket socket, const IHttpRouter& api_router) :
	m_Socket(std::move(socket)),
	m_ApiRouter(api_router)
{
}

void HttpConnection::Start()
{
	ReadRequest();
	CheckDeadline();
}

void HttpConnection::ReadRequest()
{
	auto self = shared_from_this();

	boost::beast::http::async_read(m_Socket, m_Buffer, m_Request, [self](boost::beast::error_code ec, std::size_t bytes_transferred)
		{
			boost::ignore_unused(bytes_transferred);
			if (!ec)
			{
				self->ProcessRequest();
			}
		});
}

void HttpConnection::ProcessRequest()
{
	try
	{
		switch (m_Request.method())
		{
		case boost::beast::http::verb::get:
		case boost::beast::http::verb::post:
			m_Response = m_ApiRouter.HandleRoute(m_Request);
			break;

		default:
			BOOST_LOG_TRIVIAL(warning) << L"Client used an unknown HTTP method";
			m_Response = make_400<boost::beast::http::string_body>(m_Request, "Unknown HTTP-method", "text/html");
			break;
		}
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(warning) << L"Exception occurred while processing client request: " << ex.what();
		m_Response = make_500<boost::beast::http::string_body>(m_Request, ex.what(), "text/html");
	}

	WriteResponse();
}

void HttpConnection::WriteResponse()
{
	auto self = shared_from_this();

	m_Response.content_length(m_Response.body().size());

	boost::beast::http::async_write(
		m_Socket,
		m_Response,
		[self](boost::beast::error_code ec, std::size_t)
		{
			self->m_Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);
			self->m_Deadline.cancel();
		});
}

void HttpConnection::CheckDeadline()
{
	auto self = shared_from_this();

	m_Deadline.async_wait([self](boost::beast::error_code ec)
		{
			if (!ec)
			{
				// Close socket to cancel any outstanding operation.
				self->m_Socket.close(ec);
			}
		});
}

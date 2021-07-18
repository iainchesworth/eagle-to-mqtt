#include <boost/beast/core.hpp>
#include <boost/log/trivial.hpp>

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "upload-api/http_connection.h"
#include "upload-api/upload_api.h"

UploaderAPI::UploaderAPI(boost::asio::io_context& ioc, const Options& options, const IHttpRouter& http_router) :
	IListener(ioc),
	m_Options(options),
	m_Acceptor{ m_IOContext, {boost::asio::ip::make_address(m_Options.HttpInterface()), m_Options.HttpPort() } },
	m_Socket{ m_IOContext },
	m_ApiRouter{ http_router }
{
	BOOST_LOG_TRIVIAL(info) << L"Starting Uploader API";
}

UploaderAPI::~UploaderAPI()
{
	m_Acceptor.close();
	m_Socket.close();
}

void UploaderAPI::Run()
{
	try
	{
		BOOST_LOG_TRIVIAL(debug) << L"Listening for data uploader connections on " << m_Options.HttpInterface() << L":" << m_Options.HttpPort();

		m_Acceptor.async_accept(m_Socket, [&](boost::beast::error_code ec)
			{
				if (!ec)
				{
					std::make_shared<HttpConnection>(std::move(m_Socket), m_ApiRouter)->Start();
				}

				Run();
			});
	}
	catch (const std::runtime_error& ex)
	{
		BOOST_LOG_TRIVIAL(error) << L"Exception occurred while running Uploader API - what(): " << ex.what();
	}
}

void UploaderAPI::Stop()
{
	try
	{
		BOOST_LOG_TRIVIAL(trace) << L"Closing Uploader API acceptor";
		m_Acceptor.cancel();
		m_Acceptor.close();

		if (m_Socket.is_open())
		{
			BOOST_LOG_TRIVIAL(trace) << L"Closing Uploader API socket";
			m_Socket.cancel();
			m_Socket.close();
		}
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(error) << L"Exception while stopping the Uploader API - what(): " << ex.what();
	}
}

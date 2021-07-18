#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <boost/asio.hpp>

#include "interfaces/iapiroute.h"
#include "interfaces/ihttprouter.h"
#include "interfaces/ilistener.h"
#include "options/options.h"
#include "upload-api/http_router.h"

class UploaderAPI : public IListener
{
public:
	explicit UploaderAPI(boost::asio::io_context& ioc, const Options& options, const IHttpRouter& http_router);
	virtual ~UploaderAPI();

public:
	void Run() final;
	void Stop() final;

private:
	const Options& m_Options;
	const IHttpRouter& m_ApiRouter;

private:
	boost::asio::ip::tcp::acceptor m_Acceptor;
	boost::asio::ip::tcp::socket m_Socket;
};

#endif // REST_SERVER_H

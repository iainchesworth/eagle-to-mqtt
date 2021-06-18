#ifndef IRUNNABLE_H
#define IRUNNABLE_H

#include <boost/asio.hpp>

class IRunnable
{
public:
	explicit IRunnable(boost::asio::io_context& ioc);

public:
	virtual void Run() = 0;
	virtual void Stop() = 0;

protected:
	boost::asio::io_context& m_IOContext;
};

#endif // IRUNNABLE_H

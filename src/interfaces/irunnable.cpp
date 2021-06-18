#include "interfaces/irunnable.h"

IRunnable::IRunnable(boost::asio::io_context& ioc) :
	m_IOContext(ioc)
{
}

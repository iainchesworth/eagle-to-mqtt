#include "interfaces/ilistener.h"

IListener::IListener(boost::asio::io_context& ioc) :
	IRunnable(ioc)
{
}

#include "interfaces/ipublisher.h"

IPublisher::IPublisher(boost::asio::io_context & ioc) :
	IRunnable(ioc)
{
}

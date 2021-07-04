#include "interfaces/ibridge.h"

IBridge::IBridge(boost::asio::io_context& ioc) :
	IRunnable(ioc)
{
}

#ifndef IBRIDGE_API_H
#define IBRIDGE_API_H

#include <boost/asio.hpp>

#include "interfaces/irunnable.h"

class IBridge : public IRunnable
{
public:
	explicit IBridge(boost::asio::io_context& ioc);
};

#endif // IBRIDGE_API_H

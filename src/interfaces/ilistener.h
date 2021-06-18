#ifndef IUPLOADER_API_H
#define IUPLOADER_API_H

#include <boost/asio.hpp>

#include <memory>
#include <vector>

#include "interfaces/irunnable.h"

class IListener : public IRunnable
{
public:
	explicit IListener(boost::asio::io_context& ioc);
};

typedef std::vector<std::shared_ptr<IListener>> ListenerSet;

#endif // IUPLOADER_API_H

#ifndef IMQTTCLIENT_H
#define IMQTTCLIENT_H

#include <boost/asio.hpp>

#include <memory>
#include <vector>

#include "interfaces/irunnable.h"

class IPublisher : public IRunnable
{
public:
	explicit IPublisher(boost::asio::io_context& ioc);
};

typedef std::vector<std::shared_ptr<IPublisher>> PublisherSet;

#endif // IMQTTCLIENT_H

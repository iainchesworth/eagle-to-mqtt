#ifndef INOTIFICATION_H
#define INOTIFICATION_H

#include <boost/signals2/signal.hpp>

#include <memory>

class INotification
{
public:
	virtual void Trigger(std::shared_ptr<boost::signals2::signal_base>) = 0;
};

#endif // INOTIFICATION_H

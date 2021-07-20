#ifndef NOTIFICATION_BASE_H
#define NOTIFICATION_BASE_H

#include <boost/log/trivial.hpp>
#include <boost/signals2/signal.hpp>

#include <memory>

#include "interfaces/inotification.h"

template<typename SIGNATURE>
class NotificationBase : public INotification
{
public:
	using NotificationCallback = SIGNATURE;

protected:
	virtual void Notify(boost::signals2::signal<NotificationCallback>& signal) = 0;

private:
	void Trigger(std::shared_ptr<boost::signals2::signal_base> signal_base) final
	{
		using NotificationSignal = boost::signals2::signal<NotificationCallback>;

		auto signal = std::static_pointer_cast<NotificationSignal>(signal_base);
		if (nullptr == signal)
		{
			BOOST_LOG_TRIVIAL(warning) << L"Bad conversion to NotificationSignal";
		}
		else
		{
			Notify(*signal);
		}
	}
};


#endif // NOTIFICATION_BASE_H

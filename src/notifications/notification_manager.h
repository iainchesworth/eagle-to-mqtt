#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

#include <boost/signals2/signal.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "interfaces/inotification.h"
#include "utils/singleton.h"

class NotificationManager
{
public:
	NotificationManager();

public:
	template<typename NOTIFICATION>
	boost::signals2::connection RegisterCallback(const boost::function<typename NOTIFICATION::NotificationCallback>& callback)
	{
		if (false == boost::is_base_of<INotification, NOTIFICATION>::value)
		{
			throw;  ///FIXME
		}
		else
		{
			using Signal = boost::signals2::signal<typename NOTIFICATION::NotificationCallback>;

			const auto type_name = typeid(NOTIFICATION).name();
			std::shared_ptr<Signal> signal;

			if (m_Signals.end() == m_Signals.find(type_name))
			{
				signal = std::make_shared<Signal>();
				m_Signals[type_name] = signal;
			}
			else
			{
				signal = std::static_pointer_cast<Signal>(m_Signals[type_name]);
			}

			return signal->connect(callback);
		}
	}

	void Dispatch(std::shared_ptr<INotification> notification);
	void Poll();

private:
	std::map<std::string, std::shared_ptr<boost::signals2::signal_base>, std::less<>> m_Signals;
	std::queue<std::shared_ptr<INotification>> m_Queue;
	std::mutex m_GuardMutex;
};

struct NotificationManagerSingleton : public Singleton<NotificationManager, NotificationManagerSingleton>
{
};

#endif // NOTIFICATION_MANAGER_H

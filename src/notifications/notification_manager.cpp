#include <boost/log/trivial.hpp>

#include "notifications/notification_manager.h"

NotificationManager::NotificationManager() :
	m_Signals(),
	m_Queue(),
	m_GuardMutex()
{
	BOOST_LOG_TRIVIAL(info) << L"Starting Notification Manager";
}

void NotificationManager::Dispatch(std::shared_ptr<INotification> notification)
{
	BOOST_LOG_TRIVIAL(debug) << L"Dispatching notification";
	std::lock_guard<std::mutex> guard(m_GuardMutex);
	m_Queue.push(notification);
}

void NotificationManager::Poll()
{
	BOOST_LOG_TRIVIAL(debug) << L"Triggering " << m_Queue.size() << L" notifications";

	std::lock_guard<std::mutex> guard(m_GuardMutex);

	while (!m_Queue.empty())
	{
		auto notification = m_Queue.front();

		if (auto ptr = notification.get(); nullptr == ptr)
		{
			BOOST_LOG_TRIVIAL(warning) << L"Discovered nullptr while attempting to process notification";
		}
		else if (auto iter = m_Signals.find(typeid(*ptr).name()); m_Signals.end() == iter)
		{
			BOOST_LOG_TRIVIAL(debug) << L"No subscribers to notification; not actioning trigger";
		}
		else
		{
			notification->Trigger((*iter).second);
		}

		m_Queue.pop();
	}
}

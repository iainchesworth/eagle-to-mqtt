#include <spdlog/spdlog.h>

#include "notifications/notification_manager.h"

NotificationManager::NotificationManager()
{
	spdlog::info("Starting Notification Manager");
}

void NotificationManager::Dispatch(std::shared_ptr<INotification> notification)
{
	spdlog::trace("Dispatching notification");
	std::scoped_lock guard(m_GuardMutex);
	m_Queue.push(notification);
}

void NotificationManager::Poll()
{
	spdlog::trace("Triggering {} notifications", m_Queue.size());

	std::scoped_lock guard(m_GuardMutex);

	while (!m_Queue.empty())
	{
		auto notification = m_Queue.front();

		if (auto ptr = notification.get(); nullptr == ptr)
		{
			spdlog::warn("Discovered nullptr while attempting to process notification");
		}
		else if (auto iter = m_Signals.find(typeid(*ptr).name()); m_Signals.end() == iter)
		{
			spdlog::debug("No subscribers to notification; not actioning trigger");
		}
		else
		{
			notification->Trigger((*iter).second);
		}

		m_Queue.pop();
	}
}

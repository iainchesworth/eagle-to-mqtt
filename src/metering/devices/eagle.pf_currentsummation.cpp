#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_energyusage.h"

void Eagle::ProcessFragment(const CurrentSummation& current_summation)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing total summation values (delivered and received)";

	auto energy_usage = std::make_shared<Notification_EnergyUsage>(m_EthernetMacId);

	if (current_summation.Delivered().has_value())
	{
		m_EnergyUsage.TotalDelivered = current_summation.Delivered().value();
		energy_usage->LifetimeDelivered(m_EnergyUsage.TotalDelivered);
	}
	if (current_summation.Received().has_value())
	{
		m_EnergyUsage.TotalReceived = current_summation.Received().value();
		energy_usage->LifetimeReceived(m_EnergyUsage.TotalReceived);
	}

	NotificationManagerSingleton()->Dispatch(energy_usage);
}

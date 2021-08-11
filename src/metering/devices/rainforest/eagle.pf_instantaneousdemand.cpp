#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_energyusage.h"

void Eagle::ProcessFragment(const InstantaneousDemand& instantaneous_demand)
{
	spdlog::info("Capturing instantaneous demand history element ({}W)", instantaneous_demand.Now().ValueIn<Watts>());

	auto energy_history_elem = std::make_pair(instantaneous_demand.Timestamp(), instantaneous_demand.Now());

	m_EnergyUsage.Now = instantaneous_demand.Now();
	m_EnergyUsage.History.push_back(energy_history_elem);

	auto energy_usage = std::make_shared<Notification_EnergyUsage>(m_EthernetMacId);
	energy_usage->InstantaneousDemand(m_EnergyUsage.Now);

	NotificationManagerSingleton()->Dispatch(energy_usage);
}

#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_solarapi_powerflow.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::debug("Capturing SolarAPI PowerFlow information");

	auto solarapi_powerflow_notif = std::make_shared<Notification_SolarApi_PowerFlow>(0);

	spdlog::trace("Transferring inverter production information");
	for (const auto& [inverter_id, inverter_data] : solarapi_currentdata_powerflow.Inverters())
	{
		spdlog::trace("Processing inverter {}...", inverter_id);

	}

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Day().has_value())
	{
		spdlog::trace("Processing site daily production...");
		m_EnergyProduction.Site.Today = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Day().value();
	}

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Year().has_value())
	{
		spdlog::trace("Processing site annual production...");
		m_EnergyProduction.Site.Year = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Year().value();
	}

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Total().has_value())
	{
		spdlog::trace("Processing site all-time production...");
		m_EnergyProduction.Site.AllTime = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Total().value();
	}

	NotificationManagerSingleton()->Dispatch(solarapi_powerflow_notif);
}

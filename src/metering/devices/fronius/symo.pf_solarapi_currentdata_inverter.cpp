#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_inverterinfo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_Inverter& solarapi_currentdata_inverter)
{
	spdlog::debug("Capturing SolarAPI Inverter information");

	const auto& updated_inverter_data = solarapi_currentdata_inverter.CurrentData();

	for (const auto& [inverter_id, generation_data] : updated_inverter_data)
	{
		spdlog::trace("Processing inverter {}...", inverter_id);

		auto inverterinfo_notif = std::make_shared<Notification_InverterInfo>(inverter_id);

		(*inverterinfo_notif)
			.DailyProduction(generation_data.Today)
			.AnnualProduction(generation_data.Year)
			.AllTimeProduction(generation_data.AllTime)
			.InstantaneousDemand(generation_data.InstantaneousGeneration);

		m_EnergyProduction.Inverters[inverter_id].Today = generation_data.Today;
		m_EnergyProduction.Inverters[inverter_id].Year = generation_data.Year;
		m_EnergyProduction.Inverters[inverter_id].AllTime = generation_data.AllTime;
		m_EnergyProduction.Inverters[inverter_id].InstantaneousGeneration = generation_data.InstantaneousGeneration;

		NotificationManagerSingleton()->Dispatch(inverterinfo_notif);
	}
}

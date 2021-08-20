#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include "metering/devices/fronius/symo.h"
#include "metering/devices/fronius/energy_management/energy_production_stats.h"
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

		auto inverter_it = solarapi_currentdata_powerflow.Inverters().find(inverter_id);
		Fronius::EnergyProductionStats updated_energy_stats;

		if (inverter_data.GeneratedEnergy_Day().has_value())
		{
			spdlog::debug("Updating inverter {} day's generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Day().value().ValueIn<WattHours>());
			updated_energy_stats.Today = Production(inverter_data.GeneratedEnergy_Day().value().ValueIn<WattHours>());
		} 
		else if (solarapi_currentdata_powerflow.Inverters().end() == inverter_it)
		{
			spdlog::debug("Unknown inverter {} has never been seen before (and had an invalid day generation value...ignoring", inverter_id);
		}
		else if ((*inverter_it).second.GeneratedEnergy_Day().has_value())
		{
			spdlog::debug("Unknown inverter {} has an invalid day generation value; re-using existing value...");
			updated_energy_stats.Today = Production((*inverter_it).second.GeneratedEnergy_Day().value().ValueIn<WattHours>());
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.GeneratedEnergy_Year().has_value())
		{
			spdlog::debug("Updating inverter {} year's generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Year().value().ValueIn<WattHours>());
			updated_energy_stats.Year = Production(inverter_data.GeneratedEnergy_Year().value().ValueIn<WattHours>());
		}
		else if (solarapi_currentdata_powerflow.Inverters().end() == inverter_it)
		{
			spdlog::debug("Unknown inverter {} has never been seen before (and had an invalid year generation value...ignoring", inverter_id);
		}
		else if ((*inverter_it).second.GeneratedEnergy_Year().has_value())
		{
			spdlog::debug("Unknown inverter {} has an invalid year generation value; re-using existing value...");
			updated_energy_stats.Year = Production((*inverter_it).second.GeneratedEnergy_Year().value().ValueIn<WattHours>());
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.GeneratedEnergy_Total().has_value())
		{
			spdlog::debug("Updating inverter {} all time generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Total().value().ValueIn<WattHours>());
			updated_energy_stats.AllTime = Production(inverter_data.GeneratedEnergy_Total().value().ValueIn<WattHours>());
		}
		else if (solarapi_currentdata_powerflow.Inverters().end() == inverter_it)
		{
			spdlog::debug("Unknown inverter {} has never been seen before (and had an invalid all time generation value...ignoring", inverter_id);
		}
		else if ((*inverter_it).second.GeneratedEnergy_Total().has_value())
		{
			spdlog::debug("Unknown inverter {} has an invalid all time generation value; re-using existing value...");
			updated_energy_stats.AllTime = Production((*inverter_it).second.GeneratedEnergy_Total().value().ValueIn<WattHours>());
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.InstananeousPower().has_value())
		{
			spdlog::debug("Updating inverter {} instantaneous power value to {} watts", inverter_id, inverter_data.InstananeousPower().value().ValueIn<Watts>());
			updated_energy_stats.InstantaneousGeneration = Power(inverter_data.InstananeousPower().value().ValueIn<Watts>());
		}
		else if (solarapi_currentdata_powerflow.Inverters().end() == inverter_it)
		{
			spdlog::debug("Unknown inverter {} has never been seen before (and had an invalid instantaneous power generation value...ignoring", inverter_id);
		}
		else if ((*inverter_it).second.InstananeousPower().has_value())
		{
			spdlog::debug("Unknown inverter {} has an invalid instantaneous power generation value; re-using existing value...");
			updated_energy_stats.InstantaneousGeneration = Power((*inverter_it).second.InstananeousPower().value().ValueIn<Watts>());
		}
		else
		{
			// Do nothing here.
		}

		m_EnergyProduction.Inverters.insert_or_assign(inverter_id, updated_energy_stats);
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

	if (solarapi_currentdata_powerflow.LocalSite().PowerFlow_Production().Hardware().IsInstalled())
	{
		spdlog::trace("Processing site instantaneous power production...");
		m_EnergyProduction.Site.InstantaneousGeneration = Power(solarapi_currentdata_powerflow.LocalSite().PowerFlow_Production().Measurement().Power);
	}

	NotificationManagerSingleton()->Dispatch(solarapi_powerflow_notif);
}

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include "metering/devices/fronius/symo.h"
#include "metering/devices/fronius/energy_management/energy_production_stats.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_energygeneration.h"
#include "notifications/metering/notification_invertergeneration.h"
#include "notifications/metering/notification_inverterstatus.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::debug("Capturing SolarAPI PowerFlow information");

	ProcessFragment_PowerFlow_Site(solarapi_currentdata_powerflow);
	ProcessFragment_PowerFlow_Inverters(solarapi_currentdata_powerflow);
	ProcessFragment_PowerFlow_SmartLoads(solarapi_currentdata_powerflow);
	ProcessFragment_PowerFlow_SecondaryMeters(solarapi_currentdata_powerflow);
}

void Symo::ProcessFragment_PowerFlow_Inverters(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::trace("Transferring inverter production information");

	for (const auto& [inverter_id, inverter_data] : solarapi_currentdata_powerflow.Inverters())
	{
		spdlog::trace("Processing inverter {}...", inverter_id);

		auto invertergeneration_notif = std::make_shared<Notification_InverterGeneration>(inverter_id);
		auto inverterstatus_notif = std::make_shared<Notification_InverterStatus>(inverter_id);

		Fronius::EnergyProductionStats updated_energy_stats;

		if (inverter_data.GeneratedEnergy_Day().has_value())
		{
			spdlog::debug("Updating inverter {} day's generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Day().value().ValueIn<WattHours>());
			updated_energy_stats.Today = Production(inverter_data.GeneratedEnergy_Day().value().ValueIn<WattHours>());

			// There's potentially been a change to the production statistics...report it.
			invertergeneration_notif->DailyProduction(updated_energy_stats.Today);
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.GeneratedEnergy_Year().has_value())
		{
			spdlog::debug("Updating inverter {} year's generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Year().value().ValueIn<WattHours>());
			updated_energy_stats.Year = Production(inverter_data.GeneratedEnergy_Year().value().ValueIn<WattHours>());

			// There's potentially been a change to the production statistics...report it.
			invertergeneration_notif->AnnualProduction(updated_energy_stats.Year);
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.GeneratedEnergy_Total().has_value())
		{
			spdlog::debug("Updating inverter {} all time generation value to {} watt-hours", inverter_id, inverter_data.GeneratedEnergy_Total().value().ValueIn<WattHours>());
			updated_energy_stats.AllTime = Production(inverter_data.GeneratedEnergy_Total().value().ValueIn<WattHours>());

			// There's potentially been a change to the production statistics...report it.
			invertergeneration_notif->AllTimeProduction(updated_energy_stats.AllTime);
		}
		else
		{
			// Do nothing here.
		}

		if (inverter_data.InstananeousPower().has_value())
		{
			spdlog::debug("Updating inverter {} instantaneous power value to {} watts", inverter_id, inverter_data.InstananeousPower().value().ValueIn<Watts>());
			updated_energy_stats.InstantaneousGeneration = Power(inverter_data.InstananeousPower().value().ValueIn<Watts>());

			// There's potentially been a change to the production statistics...report it.
			invertergeneration_notif->InstantaneousDemand(updated_energy_stats.InstantaneousGeneration);
		}
		else
		{
			// Do nothing here.
		}

		m_EnergyProduction.Inverters.insert_or_assign(inverter_id, updated_energy_stats);

		if (inverter_data.DeviceType().has_value())
		{
			inverterstatus_notif->DeviceType(inverter_data.DeviceType().value());
		}

		if (inverter_data.StateOfCharge().has_value())
		{
			inverterstatus_notif->StateOfCharge(inverter_data.StateOfCharge().value());
		}

		if (inverter_data.ComponentId().has_value())
		{
			inverterstatus_notif->ComponentId(inverter_data.ComponentId().value());
		}

		if (inverter_data.BatteryMode().has_value())
		{
			inverterstatus_notif->BatteryMode(inverter_data.BatteryMode().value());
		}

		NotificationManagerSingleton()->Dispatch(invertergeneration_notif);
		NotificationManagerSingleton()->Dispatch(inverterstatus_notif);
	}
}

void Symo::ProcessFragment_PowerFlow_Site(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::trace("Transferring site production information");

	auto energygeneration_notif = std::make_shared<Notification_EnergyGeneration>(0);

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Day().has_value())
	{
		spdlog::trace("Processing site daily production...");
		m_EnergyProduction.Site.Today = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Day().value();
		energygeneration_notif->DailyProduction(m_EnergyProduction.Site.Today);
	}

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Year().has_value())
	{
		spdlog::trace("Processing site annual production...");
		m_EnergyProduction.Site.Year = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Year().value();
		energygeneration_notif->AnnualProduction(m_EnergyProduction.Site.Year);
	}

	if (solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Total().has_value())
	{
		spdlog::trace("Processing site all-time production...");
		m_EnergyProduction.Site.AllTime = solarapi_currentdata_powerflow.LocalSite().GeneratedEnergy_Total().value();
		energygeneration_notif->AllTimeProduction(m_EnergyProduction.Site.AllTime);
	}

	if (solarapi_currentdata_powerflow.LocalSite().PowerFlow_Production().Hardware().IsInstalled())
	{
		spdlog::trace("Processing site instantaneous power production...");
		m_EnergyProduction.Site.InstantaneousGeneration = Power(solarapi_currentdata_powerflow.LocalSite().PowerFlow_Production().Measurement().Power);
		energygeneration_notif->InstantaneousDemand(m_EnergyProduction.Site.InstantaneousGeneration);
	}

	NotificationManagerSingleton()->Dispatch(energygeneration_notif);
}

void Symo::ProcessFragment_PowerFlow_SecondaryMeters(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::trace("Transferring secondary meter information");

}

void Symo::ProcessFragment_PowerFlow_SmartLoads(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::trace("Transferring smart load information");

}

#include <spdlog/spdlog.h>

#include <string>

#include "metering/devices/fronius/common/symo_payloads.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_inverter.h"
#include "metering/types/optional.h"

SolarApi_CurrentData_Inverter::SolarApi_CurrentData_Inverter(const boost::property_tree::ptree& node)
{
	spdlog::debug("Hydrating Fronius -> Inverter Generation Data)");

	std::unordered_map<HardwareBase::HardwareId, Production> m_DailyProduction{};
	std::unordered_map<HardwareBase::HardwareId, Production> m_AnnualProduction{};
	std::unordered_map<HardwareBase::HardwareId, Production> m_AllTimeProduction{};
	std::unordered_map<HardwareBase::HardwareId, Power> m_InstantaneousGeneration{};

	SymoPayload::Collection_GetField<decltype(m_DailyProduction)>("Body.DAY_ENERGY", m_DailyProduction, node);
	SymoPayload::Collection_GetField<decltype(m_AnnualProduction)>("Body.YEAR_ENERGY", m_AnnualProduction, node);
	SymoPayload::Collection_GetField<decltype(m_AllTimeProduction)>("Body.TOTAL_ENERGY", m_AllTimeProduction, node);
	SymoPayload::Collection_GetField<decltype(m_InstantaneousGeneration)>("Body.PAC", m_InstantaneousGeneration, node);

	std::for_each(m_DailyProduction.begin(), m_DailyProduction.end(), [this](const std::pair<HardwareBase::HardwareId, Production>& inverter_production_data)
		{ 
			Production daily_production(inverter_production_data.second.ValueIn<WattHours>());

			if (auto it = m_CurrentData.find(inverter_production_data.first); m_CurrentData.end() != it)
			{ 
				(*it).second.Today = daily_production;
			}
			else
			{
				Fronius::EnergyProductionStats energy_stats;
				energy_stats.Today = daily_production;
				m_CurrentData.insert({ inverter_production_data.first, energy_stats });
			}
		});

	std::for_each(m_AnnualProduction.begin(), m_AnnualProduction.end(), [this](const std::pair<HardwareBase::HardwareId, Production>& inverter_production_data)
		{
			Production year_production(inverter_production_data.second.ValueIn<WattHours>());

			if (auto it = m_CurrentData.find(inverter_production_data.first); m_CurrentData.end() != it)
			{
				(*it).second.Year = year_production;
			}
			else
			{
				Fronius::EnergyProductionStats energy_stats;
				energy_stats.Year = year_production;
				m_CurrentData.insert({ inverter_production_data.first, energy_stats });
			}
		});

	std::for_each(m_AllTimeProduction.begin(), m_AllTimeProduction.end(), [this](const std::pair<HardwareBase::HardwareId, Production>& inverter_production_data)
		{
			Production alltime_production(inverter_production_data.second.ValueIn<WattHours>());

			if (auto it = m_CurrentData.find(inverter_production_data.first); m_CurrentData.end() != it)
			{
				(*it).second.AllTime = alltime_production;
			}
			else
			{
				Fronius::EnergyProductionStats energy_stats;
				energy_stats.AllTime = alltime_production;
				m_CurrentData.insert({ inverter_production_data.first, energy_stats });
			}
		});

	std::for_each(m_InstantaneousGeneration.begin(), m_InstantaneousGeneration.end(), [this](const std::pair<HardwareBase::HardwareId, Power>& inverter_production_data)
		{
			Power instantaneous_generation(inverter_production_data.second.ValueIn<Watts>());

			if (auto it = m_CurrentData.find(inverter_production_data.first); m_CurrentData.end() != it)
			{
				(*it).second.InstantaneousGeneration = instantaneous_generation;
			}
			else
			{
				Fronius::EnergyProductionStats energy_stats;
				energy_stats.InstantaneousGeneration = instantaneous_generation;
				m_CurrentData.insert({ inverter_production_data.first, energy_stats });
			}
		});
}

const InverterGenerationData& SolarApi_CurrentData_Inverter::CurrentData() const
{
	return m_CurrentData;
}

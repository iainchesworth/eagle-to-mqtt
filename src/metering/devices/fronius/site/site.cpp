#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include "metering/devices/fronius/site/site.h"
#include "metering/types/essential.h"
#include "metering/types/optional.h"

Site::Site(OperatingModes mode, std::optional<bool> battery_in_standby, std::optional<bool> backup_mode, GridEnergyMeasurement powerflow_grid, LoadEnergyMeasurement powerflow_generation, AkkuEnergyMeasurement powerflow_battery, PVEnergyMeasurement powerflow_production, std::optional<Percentage> self_consumption, std::optional<Percentage> relative_autonomy, std::optional<MeterLocations> meter_location, std::optional<double> generatedenergy_day, std::optional<double> generatedenergy_year, std::optional<double> generatedenergy_total) :
	m_Mode(mode),
	m_BatteryInStandby(battery_in_standby),
	m_BackupMode(backup_mode),
	m_PowerFlow_Grid(powerflow_grid),
	m_PowerFlow_Generation(powerflow_generation),
	m_PowerFlow_Battery(powerflow_battery),
	m_PowerFlow_Production(powerflow_production),
	m_SelfConsumption(self_consumption),
	m_RelativeAutonomy(relative_autonomy),
	m_MeterLocation(meter_location),
	m_GeneratedEnergy_Day_InWh(generatedenergy_day),
	m_GeneratedEnergy_Year_InWh(generatedenergy_year),
	m_GeneratedEnergy_Total_InWh(generatedenergy_total)
{
}

OperatingModes Site::Mode() const
{
	return m_Mode;
}

std::optional<bool> Site::BatteryInStandby() const
{
	return m_BatteryInStandby;
}

std::optional<bool> Site::BackupMode() const
{
	return m_BackupMode;
}

GridEnergyMeasurement Site::PowerFlow_Grid() const
{
	return m_PowerFlow_Grid;
}

LoadEnergyMeasurement Site::PowerFlow_Generation() const
{
	return m_PowerFlow_Generation;
}

AkkuEnergyMeasurement Site::PowerFlow_Battery() const
{
	return m_PowerFlow_Battery;
}

PVEnergyMeasurement Site::PowerFlow_Production() const
{
	return m_PowerFlow_Production;
}

std::optional<Percentage> Site::SelfConsumption() const
{
	return m_SelfConsumption;
}

std::optional<Percentage> Site::RelativeAutonomy() const
{
	return m_RelativeAutonomy;
}

std::optional<MeterLocations> Site::MeterLocation() const
{
	return m_MeterLocation;
}

std::optional<double> Site::GeneratedEnergy_Day() const
{
	return m_GeneratedEnergy_Day_InWh;
}

std::optional<double> Site::GeneratedEnergy_Year() const
{
	return m_GeneratedEnergy_Year_InWh;
}

std::optional<double> Site::GeneratedEnergy_Total() const
{
	return m_GeneratedEnergy_Total_InWh;
}

Site Site::ExtractFromPayload(const boost::property_tree::ptree& node, PowerFlowVersions powerflow_version)
{
	switch (powerflow_version())
	{
	case PowerFlowVersions::Versions::Version10:
	case PowerFlowVersions::Versions::Version11:
	case PowerFlowVersions::Versions::Version12:
		{
			auto mode = IsEssential<OperatingModes>(node, "Mode");
			auto battery_standby = IsOptional<bool>(node, "BatteryStandby");
			auto backup_mode = IsOptional<bool>(node, "BackupMode");
			auto grid_em = GridEnergyMeasurement(node.get<std::string>("P_Grid"));
			auto load_em = LoadEnergyMeasurement(node.get<std::string>("P_Load"));
			auto akku_em = AkkuEnergyMeasurement(node.get<std::string>("P_Akku"));
			auto pv_em = PVEnergyMeasurement(node.get<std::string>("P_PV"));
			auto self_consumption = IsOptional<Percentage>(node, "rel_SelfConsumption");
			auto autonomy = IsOptional<Percentage>(node, "rel_Autonomy");
			auto meter_location = IsOptional<MeterLocations>(node, "Meter_Location");
			auto generated_day = IsOptional<double>(node, "E_Day");
			auto generated_year = IsOptional<double>(node, "E_Year");
			auto generated_total = IsOptional<double>(node, "E_Total");

			spdlog::debug("Hydrating Fronius -> Site (version: {})", powerflow_version);
			return Site(mode, battery_standby, backup_mode, grid_em, load_em, akku_em, pv_em, self_consumption, autonomy, meter_location, generated_day, generated_year, generated_total);
		}
		break;

	case PowerFlowVersions::Versions::NotSpecified:
	case PowerFlowVersions::Versions::Unknown:
	default:
		spdlog::warn("Cannot decode site information - unknown PowerFlow version: {}", powerflow_version);
		break;
	}

	throw; ///FIXME
}

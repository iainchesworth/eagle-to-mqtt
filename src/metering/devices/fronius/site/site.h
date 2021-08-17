#ifndef SITE_H
#define SITE_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <optional>
#include <string>

#include "metering/devices/fronius/energy_measurement/energy_measurement.h"
#include "metering/devices/fronius/messages/partial_message_types/operating_modes.h"
#include "metering/devices/fronius/messages/partial_message_types/meter_locations.h"
#include "metering/devices/fronius/messages/partial_message_types/powerflow_versions.h"
#include "metering/types/percentage.h"

class Site
{
public:
	Site(OperatingModes mode, std::optional<bool> battery_in_standby, std::optional<bool> backup_mode, GridEnergyMeasurement powerflow_grid, LoadEnergyMeasurement powerflow_generation, AkkuEnergyMeasurement powerflow_battery, PVEnergyMeasurement powerflow_production, std::optional<Percentage> self_consumption, std::optional<Percentage> relative_autonomy, std::optional<MeterLocations> meter_location, std::optional<double> generatedenergy_day, std::optional<double> generatedenergy_year, std::optional<double> generatedenergy_total);

public:
	OperatingModes Mode() const;
	std::optional<bool> BatteryInStandby() const;
	std::optional<bool> BackupMode() const;
	GridEnergyMeasurement PowerFlow_Grid() const;
	LoadEnergyMeasurement PowerFlow_Generation() const;
	AkkuEnergyMeasurement PowerFlow_Battery() const;
	PVEnergyMeasurement PowerFlow_Production() const;
	std::optional<Percentage> SelfConsumption() const;
	std::optional<Percentage> RelativeAutonomy() const;
	std::optional<MeterLocations> MeterLocation() const;
	std::optional<double> GeneratedEnergy_Day() const;
	std::optional<double> GeneratedEnergy_Year() const;
	std::optional<double> GeneratedEnergy_Total() const;

private:
	OperatingModes m_Mode;
	std::optional<bool> m_BatteryInStandby;
	std::optional<bool> m_BackupMode;
	GridEnergyMeasurement m_PowerFlow_Grid;
	LoadEnergyMeasurement m_PowerFlow_Generation;
	AkkuEnergyMeasurement m_PowerFlow_Battery;
	PVEnergyMeasurement m_PowerFlow_Production;
	std::optional<Percentage> m_SelfConsumption;
	std::optional<Percentage> m_RelativeAutonomy;
	std::optional<MeterLocations> m_MeterLocation;
	std::optional<double> m_GeneratedEnergy_Day_InWh;
	std::optional<double> m_GeneratedEnergy_Year_InWh;
	std::optional<double> m_GeneratedEnergy_Total_InWh;

public:
	static Site ExtractFromPayload(const boost::property_tree::ptree& node, PowerFlowVersions powerflow_version);
};

#endif // SITE_H

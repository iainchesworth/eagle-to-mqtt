#ifndef SITE_H
#define SITE_H

#include <boost/property_tree/ptree.hpp>

#include <any>
#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

#include "metering/common/energy_value.h"
#include "metering/devices/fronius/energy_management/grid_energy_measurement.h"
#include "metering/devices/fronius/energy_management/load_energy_measurement.h"
#include "metering/devices/fronius/energy_management/akku_energy_measurement.h"
#include "metering/devices/fronius/energy_management/pv_energy_measurement.h"
#include "metering/devices/fronius/messages_types/operating_modes.h"
#include "metering/devices/fronius/messages_types/meter_locations.h"
#include "metering/devices/fronius/messages_types/percentage.h"
#include "metering/devices/fronius/messages_types/powerflow_versions.h"

class Site
{
	static const std::string FIELDNAME_MODE;
	static const std::string FIELDNAME_BATTERYSTANDBY;
	static const std::string FIELDNAME_BACKUPMODE;
	static const std::string FIELDNAME_PGRID;
	static const std::string FIELDNAME_PLOAD;
	static const std::string FIELDNAME_PAKKU;
	static const std::string FIELDNAME_PPV;
	static const std::string FIELDNAME_SELFCONSUMPTION;
	static const std::string FIELDNAME_AUTONOMY;
	static const std::string FIELDNAME_METERLOCATION;
	static const std::string FIELDNAME_DAY;
	static const std::string FIELDNAME_YEAR;
	static const std::string FIELDNAME_TOTAL;

private:
	Site();

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
	MeterLocations MeterLocation() const;
	std::optional<Production> GeneratedEnergy_Day() const;
	std::optional<Production> GeneratedEnergy_Year() const;
	std::optional<Production> GeneratedEnergy_Total() const;

private:
	using SitePayloadFieldTypes = std::variant<OperatingModes, std::optional<bool>, GridEnergyMeasurement, LoadEnergyMeasurement, AkkuEnergyMeasurement, PVEnergyMeasurement, std::optional<Percentage>, MeterLocations, std::optional<Production>>;
	using SitePayloadFields = std::unordered_map<std::string, SitePayloadFieldTypes>;
	SitePayloadFields m_SitePayloadFields
	{
		{ FIELDNAME_MODE, OperatingModes(OperatingModes::Modes::NotSpecified) },
		{ FIELDNAME_BATTERYSTANDBY, std::optional<bool>() },
		{ FIELDNAME_BACKUPMODE, std::optional<bool>() },
		{ FIELDNAME_PGRID, GridEnergyMeasurement(std::string("0.0")) },
		{ FIELDNAME_PLOAD, LoadEnergyMeasurement(std::string("0.0")) },
		{ FIELDNAME_PAKKU, AkkuEnergyMeasurement(std::string("0.0")) },
		{ FIELDNAME_PPV, PVEnergyMeasurement(std::string("0.0")) },
		{ FIELDNAME_SELFCONSUMPTION, std::optional<Percentage>() },
		{ FIELDNAME_AUTONOMY, std::optional<Percentage>() },
		{ FIELDNAME_METERLOCATION, MeterLocations(MeterLocations::Locations::Unknown) },
		{ FIELDNAME_DAY, std::optional<Production>() },
		{ FIELDNAME_YEAR, std::optional<Production>() },
		{ FIELDNAME_TOTAL, std::optional<Production>() }

	};

public:
	static Site ExtractFromPayload(const boost::property_tree::ptree& node, PowerFlowVersions powerflow_version);
};

#endif // SITE_H

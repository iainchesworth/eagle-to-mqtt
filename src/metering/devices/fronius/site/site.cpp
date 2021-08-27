#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include "metering/devices/fronius/common/symo_payloads.h"
#include "metering/devices/fronius/site/site.h"

const std::string Site::FIELDNAME_MODE{ "Mode" };
const std::string Site::FIELDNAME_BATTERYSTANDBY{ "BatteryStandby" };
const std::string Site::FIELDNAME_BACKUPMODE{ "BackupMode" };
const std::string Site::FIELDNAME_PGRID{ "P_Grid" };
const std::string Site::FIELDNAME_PLOAD{ "P_Load" };
const std::string Site::FIELDNAME_PAKKU{ "P_Akku" };
const std::string Site::FIELDNAME_PPV{ "P_PV" };
const std::string Site::FIELDNAME_SELFCONSUMPTION{ "rel_SelfConsumption" };
const std::string Site::FIELDNAME_AUTONOMY{ "rel_Autonomy" };
const std::string Site::FIELDNAME_METERLOCATION{ "Meter_Location" };
const std::string Site::FIELDNAME_DAY{ "E_Day" };
const std::string Site::FIELDNAME_YEAR{ "E_Year" };
const std::string Site::FIELDNAME_TOTAL{ "E_Total" };

Site::Site()
{
}

OperatingModes Site::Mode() const
{
	return std::get<OperatingModes>(m_SitePayloadFields.at(FIELDNAME_MODE));
}

std::optional<bool> Site::BatteryInStandby() const
{
	return std::get<std::optional<bool>>(m_SitePayloadFields.at(FIELDNAME_BATTERYSTANDBY));
}

std::optional<bool> Site::BackupMode() const
{
	return std::get<std::optional<bool>>(m_SitePayloadFields.at(FIELDNAME_BACKUPMODE));
}

GridEnergyMeasurement Site::PowerFlow_Grid() const
{
	return std::get<GridEnergyMeasurement>(m_SitePayloadFields.at(FIELDNAME_PGRID));
}

LoadEnergyMeasurement Site::PowerFlow_Generation() const
{
	return std::get<LoadEnergyMeasurement>(m_SitePayloadFields.at(FIELDNAME_PLOAD));
}

AkkuEnergyMeasurement Site::PowerFlow_Battery() const
{
	return std::get<AkkuEnergyMeasurement>(m_SitePayloadFields.at(FIELDNAME_PAKKU));
}

PVEnergyMeasurement Site::PowerFlow_Production() const
{
	return std::get<PVEnergyMeasurement>(m_SitePayloadFields.at(FIELDNAME_PPV));
}

std::optional<Percentage> Site::SelfConsumption() const
{
	return std::get<std::optional<Percentage>>(m_SitePayloadFields.at(FIELDNAME_SELFCONSUMPTION));
}

std::optional<Percentage> Site::RelativeAutonomy() const
{
	return std::get<std::optional<Percentage>>(m_SitePayloadFields.at(FIELDNAME_AUTONOMY));
}

MeterLocations Site::MeterLocation() const
{
	return std::get<MeterLocations>(m_SitePayloadFields.at(FIELDNAME_METERLOCATION));
}

std::optional<Production> Site::GeneratedEnergy_Day() const
{
	return std::get<std::optional<Production>>(m_SitePayloadFields.at(FIELDNAME_DAY));
}

std::optional<Production> Site::GeneratedEnergy_Year() const
{
	return std::get<std::optional<Production>>(m_SitePayloadFields.at(FIELDNAME_YEAR));
}

std::optional<Production> Site::GeneratedEnergy_Total() const
{
	return std::get<std::optional<Production>>(m_SitePayloadFields.at(FIELDNAME_TOTAL));
}

Site Site::ExtractFromPayload(const boost::property_tree::ptree& node, PowerFlowVersions powerflow_version)
{
	Site local_site;

	switch (powerflow_version())
	{
	case PowerFlowVersions::Versions::Version10:
	case PowerFlowVersions::Versions::Version11:
	case PowerFlowVersions::Versions::Version12:
		spdlog::debug("Hydrating Fronius -> Site (version: {})", powerflow_version);
		for (auto& field : local_site.m_SitePayloadFields)
		{
			auto& field_name = field.first;
			auto& field_variant = field.second;

			std::visit([&field_name, &node](auto& field_element) { SymoPayload::GetField(field_name, field_element, node); }, field_variant);
		}
		break;

	case PowerFlowVersions::Versions::NotSpecified:
	case PowerFlowVersions::Versions::Unknown:
	default:
		spdlog::warn("Cannot decode site information - unknown PowerFlow version: {}", powerflow_version);
		break;
	}

	return local_site;
}

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h> // Enable logging of user-defined types.

#include "metering/devices/fronius/messages_types/inverter_data.h"

const std::string InverterData::FIELDNAME_DEVICEID{ "DID" };
const std::string InverterData::FIELDNAME_DEVICETYPE{ "DT" };
const std::string InverterData::FIELDNAME_POWER{ "P" };
const std::string InverterData::FIELDNAME_STATEOFCHARGE{ "SOC" };
const std::string InverterData::FIELDNAME_COMPONENTID{ "CID" };
const std::string InverterData::FIELDNAME_BATTERYMODE{ "Battery_Mode" };
const std::string InverterData::FIELDNAME_DAY{ "E_Day" };
const std::string InverterData::FIELDNAME_YEAR{ "E_Year" };
const std::string InverterData::FIELDNAME_TOTAL{ "E_Total" };

InverterData::InverterData() :
	SymoPayload()
{
}

InverterId InverterData::Id() const
{
	return std::get<InverterId>(m_InverterDataPayloadFields.at(FIELDNAME_DEVICEID));
}

int32_t InverterData::DeviceType() const
{
	return std::get<int32_t>(m_InverterDataPayloadFields.at(FIELDNAME_DEVICETYPE));
}

std::optional<Power> InverterData::InstananeousPower() const
{
	return std::get<std::optional<Power>>(m_InverterDataPayloadFields.at(FIELDNAME_POWER));
}

std::optional<Percentage> InverterData::StateOfCharge() const
{
	return std::get<std::optional<Percentage>>(m_InverterDataPayloadFields.at(FIELDNAME_STATEOFCHARGE));
}

uint32_t InverterData::ComponentId() const
{
	return std::get<uint32_t>(m_InverterDataPayloadFields.at(FIELDNAME_COMPONENTID));
}

std::optional<std::string> InverterData::BatteryMode() const
{
	return std::get<std::optional<std::string>>(m_InverterDataPayloadFields.at(FIELDNAME_BATTERYMODE));
}

std::optional<Production> InverterData::GeneratedEnergy_Day() const
{
	return std::get<std::optional<Production>>(m_InverterDataPayloadFields.at(FIELDNAME_DAY));
}

std::optional<Production> InverterData::GeneratedEnergy_Year() const
{
	return std::get<std::optional<Production>>(m_InverterDataPayloadFields.at(FIELDNAME_YEAR));
}

std::optional<Production> InverterData::GeneratedEnergy_Total() const
{
	return std::get<std::optional<Production>>(m_InverterDataPayloadFields.at(FIELDNAME_TOTAL));
}


InverterData InverterData::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	InverterData inverter_data;

	spdlog::debug("Hydrating Fronius -> Inverter Data)");
	for (auto& field : inverter_data.m_InverterDataPayloadFields)
	{
		auto& field_name = field.first;
		auto& field_variant = field.second;

		std::visit([&field_name, &node](auto& field_element) { GetField(field_name, field_element, node); }, field_variant);
	}

	return inverter_data;
}

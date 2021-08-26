#ifndef INVERTER_DATA_H
#define INVERTER_DATA_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>

#include "metering/common/energy_value.h"
#include "metering/devices/fronius/common/symo_payloads.h"
#include "metering/devices/fronius/hardware/hardware.h"
#include "metering/devices/fronius/messages_types/percentage.h"

class InverterData : public SymoPayload
{
	static const std::string FIELDNAME_DEVICETYPE;
	static const std::string FIELDNAME_POWER;
	static const std::string FIELDNAME_STATEOFCHARGE;
	static const std::string FIELDNAME_COMPONENTID;
	static const std::string FIELDNAME_BATTERYMODE;
	static const std::string FIELDNAME_DAY;
	static const std::string FIELDNAME_YEAR;
	static const std::string FIELDNAME_TOTAL;

private:
	InverterData(const HardwareBase::HardwareId& id);

public:
	std::optional<int32_t> DeviceType() const;
	std::optional<Power> InstananeousPower() const;
	std::optional<Percentage> StateOfCharge() const;
	std::optional<uint32_t> ComponentId() const;
	std::optional<std::string> BatteryMode() const;
	std::optional<Production> GeneratedEnergy_Day() const;
	std::optional<Production> GeneratedEnergy_Year() const;
	std::optional<Production> GeneratedEnergy_Total() const;

private:
	using InverterDataPayloadFieldTypes = std::variant<std::optional<uint32_t>, std::optional<int32_t>, std::optional<Power>, std::optional<Percentage>, std::optional<std::string>, std::optional<Production>>;
	using InverterDataPayloadFields = std::unordered_map<std::string, InverterDataPayloadFieldTypes>;
	InverterDataPayloadFields m_InverterDataPayloadFields
	{
		{ FIELDNAME_DEVICETYPE, std::optional<int32_t>() },
		{ FIELDNAME_POWER, std::optional<Power>() },
		{ FIELDNAME_STATEOFCHARGE, std::optional<Percentage>() },
		{ FIELDNAME_COMPONENTID, std::optional<uint32_t>() },
		{ FIELDNAME_BATTERYMODE, std::optional<std::string>() },
		{ FIELDNAME_DAY, std::optional<Production>() },
		{ FIELDNAME_YEAR, std::optional<Production>() },
		{ FIELDNAME_TOTAL, std::optional<Production>() }
	};

public:
	static InverterData ExtractFromPayload(const boost::property_tree::ptree& node, const HardwareBase::HardwareId& id);
};

#endif // INVERTER_DATA_H

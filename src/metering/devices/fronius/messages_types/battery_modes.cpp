#include <boost/algorithm/string.hpp>
#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages_types/battery_modes.h"

const std::string BatteryModes::NOT_SPECIFIED{ "Not Specified" };
const std::string BatteryModes::DISABLED{ "Disabled" };
const std::string BatteryModes::NORMAL{ "Normal" };
const std::string BatteryModes::SERVICE{ "Service" };
const std::string BatteryModes::CHARGEBOOST{ "Charge Boost" };
const std::string BatteryModes::NEARLYDEPLETED{ "Nearly Depleted" };
const std::string BatteryModes::SUSPENDED{ "Suspended" };
const std::string BatteryModes::CALIBRATE{ "Calibrate" };
const std::string BatteryModes::GRIDSUPPORT{ "Grid Support" };
const std::string BatteryModes::DEPLETERECOVERY{ "Deplete Recovery" };
const std::string BatteryModes::NONOPERABLE_VOLTAGE{ "Non Operable (Voltage)" };
const std::string BatteryModes::NONOPERABLE_TEMPERATURE{ "Non Operable (Temperature)" };
const std::string BatteryModes::PREHEATING{ "Preheating" };
const std::string BatteryModes::STARTUP{ "Startup" };
const std::string BatteryModes::STOPPED_TEMPERATURE{ "Stopped (Temperature)" };
const std::string BatteryModes::BATTERYFULL{ "Battery Full" };
const std::string BatteryModes::UNKNOWN{ "Unknown" };

BatteryModes::BatteryModes() :
	BatteryModes(Modes::NotSpecified)
{
}

BatteryModes::BatteryModes(Modes mode) :
	m_Mode(mode)
{
}

BatteryModes::BatteryModes(const std::string& mode) :
	m_Mode(FromString(mode))
{
}

BatteryModes::Modes BatteryModes::FromString(const std::string& mode_string)
{
	Modes mode_type = Modes::NotSpecified;

	if (0 == mode_string.length())
	{
		spdlog::warn("Invalid BatteryModes::Modes provided to converter (zero-length)");
		throw std::runtime_error("Zero-length mode value");
	}
	else if (boost::iequals(DISABLED, mode_string))
	{
		mode_type = Modes::Disabled;
	}
	else if (boost::iequals(NORMAL, mode_string))
	{
		mode_type = Modes::Normal;
	}
	else if (boost::iequals(SERVICE, mode_string))
	{
		mode_type = Modes::Service;
	}
	else if (boost::iequals(CHARGEBOOST, mode_string))
	{
		mode_type = Modes::ChargeBoost;
	}
	else if (boost::iequals(NEARLYDEPLETED, mode_string))
	{
		mode_type = Modes::NearlyDepleted;
	}
	else if (boost::iequals(SUSPENDED, mode_string))
	{
		mode_type = Modes::Suspended;
	}
	else if (boost::iequals(CALIBRATE, mode_string))
	{
		mode_type = Modes::Calibrate;
	}
	else if (boost::iequals(GRIDSUPPORT, mode_string))
	{
		mode_type = Modes::GridSupport;
	}
	else if (boost::iequals(DEPLETERECOVERY, mode_string))
	{
		mode_type = Modes::DepleteRecovery;
	}
	else if (boost::iequals(NONOPERABLE_VOLTAGE, mode_string))
	{
		mode_type = Modes::NonOperable_Voltage;
	}
	else if (boost::iequals(NONOPERABLE_TEMPERATURE, mode_string))
	{
		mode_type = Modes::NonOperable_Temperature;
	}
	else if (boost::iequals(PREHEATING, mode_string))
	{
		mode_type = Modes::PreHeating;
	}
	else if (boost::iequals(STARTUP, mode_string))
	{
		mode_type = Modes::StartUp;
	}
	else if (boost::iequals(STOPPED_TEMPERATURE, mode_string))
	{
		mode_type = Modes::Stopped_Temperature;
	}
	else if (boost::iequals(BATTERYFULL, mode_string))
	{
		mode_type = Modes::BatteryFull;
	}
	else
	{
		spdlog::warn("Unknown BatteryModes::Mode provided to converter: {}", mode_string);
		mode_type = Modes::Unknown;
	}

	return mode_type;
}

std::string BatteryModes::ToString(const Modes mode_type)
{
	switch (mode_type)
	{
	case Modes::NotSpecified:
		return NOT_SPECIFIED;
	case Modes::Disabled:
		return DISABLED;
	case Modes::Normal:
		return NORMAL;
	case Modes::Service:
		return SERVICE;
	case Modes::ChargeBoost:
		return CHARGEBOOST;
	case Modes::NearlyDepleted:
		return NEARLYDEPLETED;
	case Modes::Suspended:
		return SUSPENDED;
	case Modes::Calibrate:
		return CALIBRATE;
	case Modes::GridSupport:
		return GRIDSUPPORT;
	case Modes::DepleteRecovery:
		return DEPLETERECOVERY;
	case Modes::NonOperable_Voltage:
		return NONOPERABLE_VOLTAGE;
	case Modes::NonOperable_Temperature:
		return NONOPERABLE_TEMPERATURE;
	case Modes::PreHeating:
		return PREHEATING;
	case Modes::StartUp:
		return STARTUP;
	case Modes::Stopped_Temperature:
		return STOPPED_TEMPERATURE;
	case Modes::BatteryFull:
		return BATTERYFULL;
	case Modes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool BatteryModes::operator==(const BatteryModes& battery_mode) const
{
	return (m_Mode == battery_mode.m_Mode);
}

bool BatteryModes::operator==(const Modes& mode) const
{
	return (m_Mode == mode);
}

std::ostream& operator<<(std::ostream& os, const BatteryModes& battery_mode)
{
	os << BatteryModes::ToString(battery_mode.m_Mode);
	return os;
}

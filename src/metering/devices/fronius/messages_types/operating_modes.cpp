#include <boost/algorithm/string.hpp>
#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages_types/operating_modes.h"

const std::string OperatingModes::NOT_SPECIFIED{ "Not Specified" };
const std::string OperatingModes::PRODUCE_ONLY{ "Produce-Only" };
const std::string OperatingModes::METER{ "Meter" };
const std::string OperatingModes::VAGUE_METER{ "Vague-Meter" };
const std::string OperatingModes::BI_DIRECTIONAL{ "Bidirectional" };
const std::string OperatingModes::AC_COUPLED{ "AC-Coupled" };
const std::string OperatingModes::UNKNOWN{ "Unknown" };

OperatingModes::OperatingModes() :
	OperatingModes(Modes::NotSpecified)
{
}

OperatingModes::OperatingModes(Modes mode) :
	m_Mode(mode)
{
}

OperatingModes::OperatingModes(const std::string& mode) :
	m_Mode(FromString(mode))
{
}

OperatingModes::Modes OperatingModes::FromString(const std::string& mode_string)
{
	Modes mode_type = Modes::NotSpecified;

	if (0 == mode_string.length())
	{
		spdlog::warn("Invalid OperatingModes::Modes provided to converter (zero-length)");
		throw std::runtime_error("Zero-length mode value");
	}
	else if (boost::iequals(PRODUCE_ONLY, mode_string))
	{
		mode_type = Modes::ProduceOnly;
	}
	else if (boost::iequals(METER, mode_string))
	{
		mode_type = Modes::Meter;
	}
	else if (boost::iequals(VAGUE_METER, mode_string))
	{
		mode_type = Modes::VagueMeter;
	}
	else if (boost::iequals(BI_DIRECTIONAL, mode_string))
	{
		mode_type = Modes::BiDirectional;
	}
	else if (boost::iequals(AC_COUPLED, mode_string))
	{
		mode_type = Modes::AC_Coupled;
	}
	else
	{
		spdlog::warn("Unknown OperatingModes::Mode provided to converter: {}", mode_string);
		mode_type = Modes::Unknown;
	}

	return mode_type;
}

std::string OperatingModes::ToString(const Modes mode_type)
{
	switch (mode_type)
	{
	case Modes::NotSpecified:
		return NOT_SPECIFIED;
	case Modes::ProduceOnly:
		return PRODUCE_ONLY;
	case Modes::Meter:
		return METER;
	case Modes::VagueMeter:
		return VAGUE_METER;
	case Modes::BiDirectional:
		return BI_DIRECTIONAL;
	case Modes::AC_Coupled:
		return AC_COUPLED;
	case Modes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool OperatingModes::operator==(const OperatingModes& operating_mode) const
{
	return (m_Mode == operating_mode.m_Mode);
}

bool OperatingModes::operator==(const Modes& mode) const
{
	return (m_Mode == mode);
}

std::ostream& operator<<(std::ostream& os, const OperatingModes& operating_mode)
{
	os << OperatingModes::ToString(operating_mode.m_Mode);
	return os;
}

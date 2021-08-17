#include <boost/algorithm/string.hpp>
#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages/partial_message_types/meter_locations.h"

const std::string MeterLocations::NOT_SPECIFIED{ "Not Specified" };
const std::string MeterLocations::LOAD{ "Load" };
const std::string MeterLocations::GRID{ "Grid" };
const std::string MeterLocations::UNKNOWN{ "Unknown" };

MeterLocations::MeterLocations() :
	MeterLocations(Locations::NotSpecified)
{
}

MeterLocations::MeterLocations(Locations location) :
	m_Location(location)
{
}

MeterLocations::MeterLocations(const std::string& location) :
	m_Location(FromString(location))
{
}

MeterLocations::Locations MeterLocations::FromString(const std::string& location_string)
{
	Locations location_type = Locations::NotSpecified;

	if (0 == location_string.length())
	{
		spdlog::warn("Invalid Locations provided to converter (zero-length)");
		throw std::runtime_error("Zero-length location value");
	}
	else if (boost::iequals(LOAD, location_string))
	{
		location_type = Locations::Load;
	}
	else if (boost::iequals(GRID, location_string))
	{
		location_type = Locations::Grid;
	}
	else
	{
		spdlog::trace("Unknown Location provided to converter: {}", location_string);
		location_type = Locations::Unknown;
	}

	return location_type;
}

std::string MeterLocations::ToString(const Locations location_type)
{
	switch (location_type)
	{
	case Locations::NotSpecified:
		return NOT_SPECIFIED;
	case Locations::Load:
		return LOAD;
	case Locations::Grid:
		return GRID;
	case Locations::Unknown:
	default:
		return UNKNOWN;
	}
}

bool MeterLocations::operator==(const MeterLocations& meter_location) const
{
	return (m_Location == meter_location.m_Location);
}

bool MeterLocations::operator==(const Locations& location) const
{
	return (m_Location == location);
}

std::ostream& operator<<(std::ostream& os, const MeterLocations& meter_location)
{
	os << MeterLocations::ToString(meter_location.m_Location);
	return os;
}

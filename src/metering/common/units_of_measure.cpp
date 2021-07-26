#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>

#include "exceptions/invalid_unitsofmeasure_value.h"
#include "metering/common/units_of_measure.h"

const std::string UnitsOfMeasure::NOT_SPECIFIED{ "Not Specified" };
const std::string UnitsOfMeasure::WATTS{ "Watts" };
const std::string UnitsOfMeasure::KILOWATTS{ "Kilowatts" };
const std::string UnitsOfMeasure::WATT_HOURS{ "Watt-Hours" };
const std::string UnitsOfMeasure::KILOWATT_HOURS{ "Kilowatt-Hours" };
const std::string UnitsOfMeasure::UNKNOWN{ "Unknown" };

UnitsOfMeasure::UnitsOfMeasure() :
	UnitsOfMeasure(Units::NotSpecified)
{
}

UnitsOfMeasure::UnitsOfMeasure(Units units) :
	m_Units(units)
{
}

UnitsOfMeasure::UnitsOfMeasure(const std::string& units) :
	m_Units(FromString(units))
{
}

UnitsOfMeasure::Units UnitsOfMeasure::FromString(const std::string& units_string)
{
	Units units = Units::NotSpecified;

	if (0 == units_string.length())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Invalid Units provided to converter (zero-length)";
		throw InvalidUnitsOfMeasureValue("Zero-length units value");
	}
	else if ((boost::iequals(units_string, "W")) || (boost::iequals(units_string, "WATTS")))
	{
		units = Units::Watts;
	}
	else if ((boost::iequals(units_string, "WH")) || (boost::iequals(units_string, "WATTHOURS")))
	{
		units = Units::WattHours;
	}
	else if ((boost::iequals(units_string, "KW")) || (boost::iequals(units_string, "KILOWATTS")))
	{
		units = Units::Kilowatts;
	}
	else if ((boost::iequals(units_string, "KWH")) || (boost::iequals(units_string, "KILOWATTHOURS")))
	{
		units = Units::KilowattHours;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Units provided to converter: " << units_string;
		units = Units::Unknown;
	}

	return units;
}

std::string UnitsOfMeasure::ToString(const Units units)
{
	switch (units)
	{
	case Units::NotSpecified:
		return NOT_SPECIFIED;
	case Units::Watts:
		return WATTS;
	case Units::Kilowatts:
		return KILOWATTS;
	case Units::WattHours:
		return WATT_HOURS;
	case Units::KilowattHours:
		return KILOWATT_HOURS;
	case Units::Unknown:
	default:
		return UNKNOWN;
	}
}

UnitsOfMeasure::Units UnitsOfMeasure::operator()() const
{
	return m_Units;
}

bool UnitsOfMeasure::operator==(const UnitsOfMeasure& other) const
{
	return (m_Units == other.m_Units);
}

bool UnitsOfMeasure::operator==(const Units& units) const
{
	return (m_Units == units);
}

std::ostream& operator<<(std::ostream& os, const UnitsOfMeasure& units)
{
	os << UnitsOfMeasure::ToString(units.m_Units);
	return os;
}

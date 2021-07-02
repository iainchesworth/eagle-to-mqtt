#ifndef CALCULATED_ENERGY_VALUE_H
#define CALCULATED_ENERGY_VALUE_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <string>

#include "metering/common/unit_converters.h"
#include "metering/common/units_of_measure.h"
#include "metering/type_handlers/essential.h"

class CalculatedEnergyValue
{
public:
	CalculatedEnergyValue(uint32_t raw_summation, uint32_t multiplier, uint32_t divisor, UnitsOfMeasure units, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	virtual double EnergyValue() const;

private:
	double m_EnergyValue;

protected:
	template<typename ENERGY_VALUE>
	static ENERGY_VALUE ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key)
	{
		return ENERGY_VALUE(
			IsEssential<int64_t>(node, raw_value_key),
			IsEssential<uint32_t>(node, "Multiplier"),
			IsEssential<uint32_t>(node, "Divisor"),
			IsEssential<uint8_t>(node, "DigitsRight"),
			IsEssential<uint8_t>(node, "DigitsLeft"),
			IsEssential<bool>(node, "SuppressLeadingZero")
		);
	}
};

#endif // CALCULATED_ENERGY_VALUE_H

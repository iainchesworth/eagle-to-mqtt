#ifndef SUMMATION_IN_WATTHOURS_H
#define SUMMATION_IN_WATTHOURS_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <string>

#include "metering/common/calculated_energy_value.h"
#include "metering/common/units_of_measure.h"

class Summation : public CalculatedEnergyValue
{
public:
	Summation(uint32_t raw_summation, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	virtual double EnergyValue(UnitsOfMeasure units = UnitsOfMeasure::Units::KilowattHours) const final;

public:
	static Summation ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key);
};

#endif // SUMMATION_IN_WATTHOURS_H

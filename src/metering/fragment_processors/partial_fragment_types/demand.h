#ifndef DEMAND_H
#define DEMAND_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <string>

#include "metering/common/calculated_energy_value.h"
#include "metering/common/units_of_measure.h"

class Demand : public CalculatedEnergyValue
{
public:
	Demand(uint32_t raw_demand, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	virtual double EnergyValue(UnitsOfMeasure units = UnitsOfMeasure::Kilowatts) const final;

public:
	static Demand ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key = "Demand");
};

#endif // DEMAND_H

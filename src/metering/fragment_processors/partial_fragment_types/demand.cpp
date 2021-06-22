#include "metering/common/units_of_measure.h"
#include "metering/fragment_processors/partial_fragment_types/demand.h"

Demand::Demand(uint32_t raw_demand, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero) :
	CalculatedEnergyValue(raw_demand, multiplier, divisor, UnitsOfMeasure::Kilowatts, digits_right, digits_left, suppress_leading_zero)
{
}

Demand Demand::ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key)
{
	return CalculatedEnergyValue::ExtractFromPayload<Demand>(node, raw_value_key);
}

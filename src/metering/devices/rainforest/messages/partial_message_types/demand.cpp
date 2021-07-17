#include "metering/common/units_of_measure.h"
#include "metering/devices/rainforest/messages/partial_message_types/demand.h"

Demand::Demand(uint32_t raw_demand, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero) :
	CalculatedEnergyValue(raw_demand, multiplier, divisor, UnitsOfMeasure::Units::Kilowatts, digits_right, digits_left, suppress_leading_zero)
{
}

double Demand::EnergyValue(UnitsOfMeasure units) const
{
	switch (units())
	{
	case UnitsOfMeasure::Units::Watts:
		return CalculatedEnergyValue::EnergyValue() * 1000.0f;

	case UnitsOfMeasure::Units::Kilowatts:
		return CalculatedEnergyValue::EnergyValue();
	
	default:
		throw std::invalid_argument("Units!");
	}
}

Demand Demand::ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key)
{
	return CalculatedEnergyValue::ExtractFromPayload<Demand>(node, raw_value_key);
}

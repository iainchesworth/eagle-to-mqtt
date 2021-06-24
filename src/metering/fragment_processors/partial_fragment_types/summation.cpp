#include "metering/common/units_of_measure.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"

Summation::Summation(uint32_t raw_summation, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero) :
	CalculatedEnergyValue(raw_summation, multiplier, divisor, UnitsOfMeasure::KilowattHours, digits_right, digits_left, suppress_leading_zero)
{
}

double Summation::EnergyValue(UnitsOfMeasure units) const
{
	switch (units)
	{
	case UnitsOfMeasure::WattHours:
		return CalculatedEnergyValue::EnergyValue() * 1000.0f;

	case UnitsOfMeasure::KilowattHours:
		return CalculatedEnergyValue::EnergyValue();

	default:
		throw std::invalid_argument("Units!");
	}
}

Summation Summation::ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& raw_value_key)
{
	return CalculatedEnergyValue::ExtractFromPayload<Summation>(node, raw_value_key);
}

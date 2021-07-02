#include <boost/log/trivial.hpp>

#include "metering/common/calculated_energy_value.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/integer.h"

CalculatedEnergyValue::CalculatedEnergyValue(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, UnitsOfMeasure units, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero)
{
	// Convert the unsigned value (0x......) to signed and then store it in a double...
	double converted_energy_value = static_cast<double>(unsigned_to_signed(raw_energy_value));

	converted_energy_value *= (0 == multiplier) ? 1 : multiplier; // Multiply raw value by to get actual; if zero, use 1
	converted_energy_value /= (0 == divisor) ? 1 : divisor;		// Divide raw value by to get actual; if zero, use 1

	switch (units)
	{
	case UnitsOfMeasure::Kilowatts:
		m_EnergyValue = converted_energy_value;
		break;

	case UnitsOfMeasure::KilowattHours:
		m_EnergyValue = converted_energy_value;
		break;

	default:
		BOOST_LOG_TRIVIAL(warning) << L"Unknown units of measure specified while calculating energy value";
		m_EnergyValue = -1;
		break;
	}
}

double CalculatedEnergyValue::EnergyValue() const
{
	return m_EnergyValue;
}

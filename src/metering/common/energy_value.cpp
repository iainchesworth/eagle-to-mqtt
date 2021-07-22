#include <boost/core/ignore_unused.hpp>

#include "metering/common/energy_value.h"
#include "metering/common/unit_converters.h"

Energy::Energy(double energy_value) :
	m_EnergyValue{ energy_value }
{
}

Energy::Energy(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero)
{
	boost::ignore_unused(digits_right);
	boost::ignore_unused(digits_left);
	boost::ignore_unused(suppress_leading_zero);

	// Convert the unsigned value (0x......) to signed and then store it in a double...
	auto converted_energy_value = static_cast<double>(unsigned_to_signed(raw_energy_value));

	converted_energy_value *= (0 == multiplier) ? 1 : multiplier; // Multiply raw value by to get actual; if zero, use 1
	converted_energy_value /= (0 == divisor) ? 1 : divisor;		// Divide raw value by to get actual; if zero, use 1

	m_EnergyValue = converted_energy_value;
}

double Energy::Value() const
{
	return m_EnergyValue;
}

//=====================================================================================================================
//
//
//
//=====================================================================================================================

Usage::Usage(double usage_in_watt_hours) :
	Energy(usage_in_watt_hours)
{
}

Usage::Usage(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero) :
	Energy(raw_energy_value, multiplier, divisor, digits_right, digits_left, suppress_leading_zero)
{
}

//=====================================================================================================================
//
//
//
//=====================================================================================================================

Power::Power(double usage_in_watts) :
	Energy(usage_in_watts)
{
}

Power::Power(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero) :
	Energy(raw_energy_value, multiplier, divisor, digits_right, digits_left, suppress_leading_zero)
{
}

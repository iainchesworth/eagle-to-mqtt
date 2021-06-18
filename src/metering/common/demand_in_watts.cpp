#include <boost/log/trivial.hpp>

#include <limits>

#include "metering/common/demand_in_watts.h"

DemandInWatts::DemandInWatts(uint32_t raw_demand, uint32_t multiplier, uint32_t divisor, UnitsOfMeasure units, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero)
{
	// Convert the unsigned value (0x......) to signed and then store it in a double...
	double converted_demand = ConvertUnsignedToSigned(raw_demand);

	converted_demand *= (0 == multiplier) ? 1 : multiplier; // Multiply raw value by to get actual; if zero, use 1
	converted_demand /= (0 == divisor) ? 1 : divisor;		// Divide raw value by to get actual; if zero, use 1

	switch (units)
	{
	case UnitsOfMeasure::Kilowatts:
		m_DemandInWatts = converted_demand * 1000;
		break;

	default:
		BOOST_LOG_TRIVIAL(warning) << L"Unknown units of measure specified while calculating demand";
		m_DemandInWatts = -1;
		break;
	}
}


double DemandInWatts::Demand() const
{
	return m_DemandInWatts;
}

int32_t DemandInWatts::ConvertUnsignedToSigned(uint32_t raw_value)
{
	int32_t converted_value;

	if (std::numeric_limits<int32_t>::max() >= raw_value)
	{
		converted_value = static_cast<int32_t>(raw_value);
	}
	else if (std::numeric_limits<int32_t>::min() <= raw_value)
	{
		converted_value = -(static_cast<int32_t>(~raw_value) - 1);
	}
	else
	{
		converted_value = std::numeric_limits<int32_t>::min();
	}

	return converted_value;
}

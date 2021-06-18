#ifndef DEMAND_IN_WATTS_H
#define DEMAND_IN_WATTS_H

#include <cstdint>

#include "metering/common/units_of_measure.h"

class DemandInWatts
{
public:
	DemandInWatts(uint32_t raw_demand, uint32_t multiplier, uint32_t divisor, UnitsOfMeasure units, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	double Demand() const;

private:
	int32_t ConvertUnsignedToSigned(uint32_t raw_value);

private:
	double m_DemandInWatts;
};

#endif // DEMAND_IN_WATTS_H

#ifndef ENERGY_VALUE_H
#define ENERGY_VALUE_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <type_traits>

#include "metering/types/essential.h"

class Energy
{
public:
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

protected:
	explicit Energy(double energy_value);
	Energy(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

protected:
	double Value() const;

private:
	double m_EnergyValue;
};

//=====================================================================================================================
//
//
//
//=====================================================================================================================

struct EnergyUnits {};
struct EnergyTimeUnits {};

struct Watts : EnergyUnits
{
	double operator()(double base_value_in_watts) const { return base_value_in_watts; }
};
struct Kilowatts : EnergyUnits 
{
	double operator()(double base_value_in_watts) const { return base_value_in_watts / 1000.f; }
};

struct WattHours : EnergyTimeUnits
{
	double operator()(double base_value_in_watthours) const { return base_value_in_watthours; }
};
struct KilowattHours : EnergyTimeUnits
{
	double operator()(double base_value_in_watthours) const { return base_value_in_watthours / 1000.f; }
};

//=====================================================================================================================
//
// Usage(10.0f).ValueIn<WattHours>();
// Usage(12345, 12, 34, 2, 1, false).ValueIn<KilowattHours>();
//
//=====================================================================================================================

class Usage : public Energy
{
public:
	explicit Usage(double usage_in_watt_hours);
	Usage(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	template<typename ENERGY_TYPE, std::enable_if_t<std::is_base_of_v<EnergyTimeUnits, ENERGY_TYPE>, bool> = true>
	double ValueIn() const
	{
		return ENERGY_TYPE()(Value());
	}
};

//=====================================================================================================================
//
// Power(10.0f).ValueIn<Watts>();
// Power(12345, 12, 34, 2, 1, false).ValueIn<Kilowatts>();
//
//=====================================================================================================================

class Power : public Energy
{
public:
	explicit Power(double usage_in_watts);
	Power(uint32_t raw_energy_value, uint32_t multiplier, uint32_t divisor, uint8_t digits_right, uint8_t digits_left, bool suppress_leading_zero);

public:
	template<typename ENERGY_TYPE, std::enable_if_t<std::is_base_of_v<EnergyUnits, ENERGY_TYPE>, bool> = true>
	double ValueIn() const
	{
		return ENERGY_TYPE()(Value());
	}
};

#endif // ENERGY_VALUE_H

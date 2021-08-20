#ifndef ENERGY_MEASUREMENT_H
#define ENERGY_MEASUREMENT_H

#include <boost/optional.hpp>
#include <spdlog/spdlog.h>

#include <ostream>
#include <string>
#include <tuple>

#include "metering/common/energy_value.h"
#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"
#include "metering/devices/fronius/hardware/battery.h"
#include "metering/devices/fronius/hardware/inverter.h"
#include "metering/devices/fronius/hardware/smart_meter.h"

template<typename REQUIRED_HARDWARE, typename ENERGY_FLOWS>
class EnergyMeasurementBase
{
	static inline const std::string NULL_VALUE{ "null" };

public:
	explicit EnergyMeasurementBase(const std::string& energy_string) :
		EnergyMeasurementBase(FromString(energy_string))
	{
	}

private:
	explicit EnergyMeasurementBase(bool is_installed, double measurement) :
		m_RequiredHardware(is_installed),
		m_EnergyMeasurement{ measurement, ENERGY_FLOWS()(measurement) }
	{
	}

public:
	static EnergyMeasurementBase<REQUIRED_HARDWARE, ENERGY_FLOWS> FromString(const std::string& energy_string)
	{
		if ((0 == energy_string.length()) || (NULL_VALUE == energy_string))
		{
			spdlog::trace("EnergyMeasurement value is missing or set to null - marking as not enabled");
			return EnergyMeasurementBase<REQUIRED_HARDWARE, ENERGY_FLOWS>(false, 0.0f);
		}
		else
		{
			try
			{
				double measurement_value = std::stod(energy_string, nullptr);
				return EnergyMeasurementBase(true, measurement_value);
			}
			catch (const std::invalid_argument& ex_ia)
			{
				spdlog::debug("Failed while processing double string (argument was invalid)");
				spdlog::debug("Invalid double string (invalid_argument exception) was: {}", energy_string);
			}
			catch (const std::out_of_range& ex_oor)
			{
				spdlog::debug("Failed while processing double string (argument was outside supported type range)");
				spdlog::debug("Invalid double string (out_of_range exception) was: {}", energy_string);
			}

			// Something went wrong (and we couldn't extract a sensible value) --> mark as not enabled
			spdlog::trace("EnergyMeasurement value could not be extracted - marking as not enabled");
			return EnergyMeasurementBase<REQUIRED_HARDWARE, ENERGY_FLOWS>(false, 0.0f);
		}
	}

public:
	struct PropertyTreeTranslator
	{
		using external_type = EnergyMeasurementBase<REQUIRED_HARDWARE, ENERGY_FLOWS>;
		using internal_type = std::string;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

public:
	REQUIRED_HARDWARE Hardware() const
	{
		return m_RequiredHardware;
	}

public:
	struct EnergyMeasurement
	{
		double Power;
		typename ENERGY_FLOWS::FlowMeanings Direction;
	};
	
	EnergyMeasurement Measurement() const
	{
		return m_EnergyMeasurement;
	}

public:
	friend std::ostream& operator<<(std::ostream& os, const EnergyMeasurementBase<REQUIRED_HARDWARE, ENERGY_FLOWS>& energy_measurement)
	{
		if (energy_measurement.Hardware().IsInstalled())
		{
			os << std::fixed << std::setprecision(2) << energy_measurement.Measurement().Power << " " << energy_measurement.Measurement().Direction;
		}
		else
		{
			os << m_RequiredHardware; // Output the installation status of the required hardware (i.e. NOT)
		}

		return os;
	}

private:
	REQUIRED_HARDWARE m_RequiredHardware;
	EnergyMeasurement m_EnergyMeasurement;
};

#endif // ENERGY_MEASUREMENT_H

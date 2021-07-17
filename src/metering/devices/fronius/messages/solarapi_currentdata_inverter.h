#ifndef SOLARAPI_CURRENTDATA_INVERTER_H
#define SOLARAPI_CURRENTDATA_INVERTER_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>

#include "metering/common/base_energy_value.h"
#include "metering/types/collection.h"

class SolarApi_CurrentData_Inverter
{
public:
	SolarApi_CurrentData_Inverter(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_Inverter();

public:
	NamedCollection<int64_t> Power_AC() const;
	NamedCollection<double> GeneratedEnergy_Day() const;
	NamedCollection<double> GeneratedEnergy_Year() const;
	NamedCollection<double> GeneratedEnergy_AllTime() const;

private:
	NamedCollection<int64_t> m_Power_AC;
	NamedCollection<double> m_GeneratedEnergy_Day;
	NamedCollection<double> m_GeneratedEnergy_Year;
	NamedCollection<double> m_GeneratedEnergy_AllTime;
};

#endif // SOLARAPI_CURRENTDATA_INVERTER_H

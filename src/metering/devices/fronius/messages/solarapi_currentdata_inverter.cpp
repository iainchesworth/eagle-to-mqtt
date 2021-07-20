#include "metering/devices/fronius/messages/solarapi_currentdata_inverter.h"
#include "metering/types/collection.h"
#include "metering/types/optional.h"

SolarApi_CurrentData_Inverter::SolarApi_CurrentData_Inverter(const boost::property_tree::ptree& node) :
	m_Power_AC(Collection<int64_t>(node, "Body.PAC")),
	m_GeneratedEnergy_Day(Collection<double>(node, "Body.DAY_ENERGY")),
	m_GeneratedEnergy_Year(Collection<double>(node, "Body.YEAR_ENERGY")),
	m_GeneratedEnergy_AllTime(Collection<double>(node, "Body.TOTAL_ENERGY"))
{
}

NamedCollection<int64_t> SolarApi_CurrentData_Inverter::Power_AC() const
{
	return m_Power_AC;
}

NamedCollection<double> SolarApi_CurrentData_Inverter::GeneratedEnergy_Day() const
{
	return m_GeneratedEnergy_Day;
}

NamedCollection<double> SolarApi_CurrentData_Inverter::GeneratedEnergy_Year() const
{
	return m_GeneratedEnergy_Year;
}

NamedCollection<double> SolarApi_CurrentData_Inverter::GeneratedEnergy_AllTime() const
{
	return m_GeneratedEnergy_AllTime;
}

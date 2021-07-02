#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const InstantaneousDemand& instantaneous_demand)
{
	BOOST_LOG_TRIVIAL(info) << L"Capturing instantaneous demand history element (" << instantaneous_demand.Now().EnergyValue(UnitsOfMeasure::Watts) << L"W)";

	auto energy_history_elem = std::make_pair(instantaneous_demand.Timestamp(), instantaneous_demand.Now());

	m_EnergyUsage.Now = instantaneous_demand.Now();
	m_EnergyUsage.History.insert(energy_history_elem);
}

#include <boost/log/trivial.hpp>

#include "serialization/rainforest/deviceenergyusage_serializer.h"

using namespace Rainforest;

DeviceEnergyUsage_Serializer::DeviceEnergyUsage_Serializer(const DeviceEnergyUsage& deu) :
	ISerializer(deu)
{
}

boost::json::object DeviceEnergyUsage_Serializer::Serialize() const
{
	boost::json::object device_stats;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing Rainforest::DeviceEnergyUsage";

	device_stats["TotalDelivered_kWh"] = static_cast<std::int64_t>(m_Serializable.TotalDelivered.EnergyValue());
	device_stats["TotalReceived_kWh"] = static_cast<std::int64_t>(m_Serializable.TotalReceived.EnergyValue());
	device_stats["InstantaneousDemand_Watts"] = static_cast<std::int64_t>(m_Serializable.Now.EnergyValue(UnitsOfMeasure::Units::Watts));

	BOOST_LOG_TRIVIAL(trace) << L"Serializing " << m_Serializable.History.size() << L" history elements";

	boost::json::object history;

	for (const auto& energy_history_elem : m_Serializable.History)
	{
		const auto& usage_datetime = energy_history_elem.first;
		const auto& demand_in_watts = energy_history_elem.second.EnergyValue(UnitsOfMeasure::Units::Watts);

		history.insert({ {ZigbeeTimepoint::ToString(usage_datetime), static_cast<std::int64_t>(demand_in_watts)} });
	}

	device_stats["History"] = std::move(history);

	return device_stats;
}

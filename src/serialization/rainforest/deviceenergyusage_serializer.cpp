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

	device_stats["TotalDelivered_kWh"] = static_cast<std::int64_t>(m_Serializable.TotalDelivered.ValueIn<KilowattHours>());
	device_stats["TotalReceived_kWh"] = static_cast<std::int64_t>(m_Serializable.TotalReceived.ValueIn<KilowattHours>());
	device_stats["InstantaneousDemand_Watts"] = static_cast<std::int64_t>(m_Serializable.Now.ValueIn<Watts>());

	BOOST_LOG_TRIVIAL(trace) << L"Serializing " << m_Serializable.History.size() << L" history elements";

	boost::json::object history;

	for (const auto& [zigbee_timepoint, power] : m_Serializable.History)
	{
		history.insert({ {ZigbeeTimepoint::ToString(zigbee_timepoint), power.ValueIn<Watts>()} });
	}

	device_stats["History"] = std::move(history);

	return device_stats;
}

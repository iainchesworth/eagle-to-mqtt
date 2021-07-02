#include <boost/log/trivial.hpp>

#include "serialization/deviceenergyusage_serializer.h"

DeviceEnergyUsage_Serializer::DeviceEnergyUsage_Serializer(std::shared_ptr<DeviceEnergyUsage> ds_ptr) :
	ISerializer(ds_ptr)
{
}

boost::json::object DeviceEnergyUsage_Serializer::Serialize() const
{
	auto deu_ptr = std::static_pointer_cast<DeviceEnergyUsage>(m_Serializable);
	boost::json::object device_stats;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing DeviceEnergyUsage";

	device_stats["TotalDelivered_kWh"] = static_cast<std::int64_t>(deu_ptr->TotalDelivered.EnergyValue());
	device_stats["TotalReceived_kWh"] = static_cast<std::int64_t>(deu_ptr->TotalReceived.EnergyValue());
	device_stats["InstantaneousDemand_Watts"] = static_cast<std::int64_t>(deu_ptr->Now.EnergyValue(UnitsOfMeasure::Watts));

	BOOST_LOG_TRIVIAL(trace) << L"Serializing " << deu_ptr->History.size() << L" history elements";

	boost::json::object history;

	for (const auto& energy_history_elem : deu_ptr->History)
	{
		const auto& usage_datetime = energy_history_elem.first;
		const auto& demand_in_watts = energy_history_elem.second.EnergyValue(UnitsOfMeasure::Watts);

		history.insert({ {Timestamps::ToString(usage_datetime), static_cast<std::int64_t>(demand_in_watts)} });
	}

	device_stats["History"] = std::move(history);

	return device_stats;
}

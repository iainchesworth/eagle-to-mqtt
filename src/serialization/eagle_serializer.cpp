#include "serialization/devicestatistics_serializer.h"
#include "serialization/eagle_serializer.h"

Eagle_Serializer::Eagle_Serializer(std::shared_ptr<Eagle> eagle_ptr) :
	ISerializer(eagle_ptr)
{
}

boost::json::object Eagle_Serializer::Serialize() const
{
	auto eagle_ptr = std::static_pointer_cast<Eagle>(m_Serializable);
	boost::json::object device_object;

	device_object["ZigbeeId"] = ZigBeeMacId::ToString(eagle_ptr->m_ZigbeeMacId);
	device_object["Firmware"] = eagle_ptr->m_FirmwareVersion;
	device_object["Hardware"] = eagle_ptr->m_HardwareVersion;
	device_object["Model"] = eagle_ptr->m_ModelId;

	// Device Statistics
	DeviceStatistics_Serializer ds_serializer(std::make_shared<DeviceStatistics>(eagle_ptr->m_Statistics));
	device_object["Stats"] = ds_serializer.Serialize();

	// Energy Usage
	boost::json::object energy_usage;

	energy_usage["TotalDelivered_kWh"] = eagle_ptr->m_TotalDelivered.EnergyValue();
	energy_usage["TotalReceived_kWh"] = eagle_ptr->m_TotalReceived.EnergyValue();

	using demand_pair_type = decltype(eagle_ptr->m_DemandHistory)::value_type;
	auto latest_demand_it = std::max_element(eagle_ptr->m_DemandHistory.begin(), eagle_ptr->m_DemandHistory.end(),
		[](const demand_pair_type& p1, const demand_pair_type& p2)
		{
			return p1.first < p2.first;
		});

	if (eagle_ptr->m_DemandHistory.cend() != latest_demand_it)
	{
		const auto& latest_id_in_watts = (*latest_demand_it).second.EnergyValue(UnitsOfMeasure::Watts);
		energy_usage["InstantaneousDemand_Watts"] = latest_id_in_watts;
	}

	for (const auto& energy_history_elem : eagle_ptr->m_DemandHistory)
	{
		const auto& usage_datetime = energy_history_elem.first;
		const auto& demand_in_watts = energy_history_elem.second.EnergyValue(UnitsOfMeasure::Watts);

		energy_usage["History"].emplace_object()[Timestamps::ToString(usage_datetime)] = demand_in_watts;
	}

	device_object["EnergyUsage"] = energy_usage;

	// Meter Messages

	// Network Info

	// Price Cluster

	return device_object;
}

#include <boost/log/trivial.hpp>

#include "serialization/deviceconnectivity_serializer.h"
#include "serialization/deviceenergyusage_serializer.h"
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

	BOOST_LOG_TRIVIAL(debug) << L"Serializing Eagle";

	device_object["ZigbeeId"] = ZigBeeMacId::ToString(eagle_ptr->m_ZigbeeMacId);
	device_object["Firmware"] = eagle_ptr->m_FirmwareVersion;
	device_object["Hardware"] = eagle_ptr->m_HardwareVersion;
	device_object["Model"] = eagle_ptr->m_ModelId;

	// Connectivity
	DeviceConnectivity_Serializer dc_serializer(std::make_shared<DeviceConnectivity>(eagle_ptr->m_Connectivity));
	device_object["Connectivity"] = dc_serializer.Serialize();

	// Energy Usage
	DeviceEnergyUsage_Serializer deu_serializer(std::make_shared<DeviceEnergyUsage>(eagle_ptr->m_EnergyUsage));
	device_object["EnergyUsage"] = deu_serializer.Serialize();

	// Device Statistics
	DeviceStatistics_Serializer ds_serializer(std::make_shared<DeviceStatistics>(eagle_ptr->m_Statistics));
	device_object["Stats"] = ds_serializer.Serialize();

	// Meter Messages

	// Network Info

	// Price Cluster

	return device_object;
}

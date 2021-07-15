#include <boost/log/trivial.hpp>

#include "serialization/rainforest/deviceconnectivity_serializer.h"
#include "serialization/rainforest/deviceenergyusage_serializer.h"
#include "serialization/rainforest/devicestatistics_serializer.h"
#include "serialization/rainforest/eagle_serializer.h"

Eagle_Serializer::Eagle_Serializer(const Eagle& eagle) :
	ISerializer(eagle)
{
}

boost::json::object Eagle_Serializer::Serialize() const
{
	boost::json::object device_object;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing Eagle";

	device_object["ZigbeeId"] = ZigBeeMacId::ToString(m_Serializable.m_ZigbeeMacId);
	device_object["Firmware"] = m_Serializable.m_FirmwareVersion;
	device_object["Hardware"] = m_Serializable.m_HardwareVersion;
	device_object["Model"] = m_Serializable.m_ModelId;

	// Connectivity
	Rainforest::DeviceConnectivity_Serializer dc_serializer(m_Serializable.m_Connectivity);
	device_object["Connectivity"] = dc_serializer.Serialize();

	// Energy Usage
	Rainforest::DeviceEnergyUsage_Serializer deu_serializer(m_Serializable.m_EnergyUsage);
	device_object["EnergyUsage"] = deu_serializer.Serialize();

	// Device Statistics
	Rainforest::DeviceStatistics_Serializer ds_serializer(m_Serializable.m_Statistics);
	device_object["Stats"] = ds_serializer.Serialize();

	// Meter Messages

	// Network Info

	// Price Cluster

	return device_object;
}

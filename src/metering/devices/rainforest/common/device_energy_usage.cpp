#include "metering/devices/rainforest/common/device_energy_usage.h"
#include "serialization/rainforest/deviceenergyusage_serializer.h"

using namespace Rainforest;

DeviceEnergyUsage::DeviceEnergyUsage()
{
}

boost::json::object DeviceEnergyUsage::Serialize() const
{
	return DeviceEnergyUsage_Serializer(*this).Serialize();
}

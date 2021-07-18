#include "metering/devices/rainforest/common/device_energy_usage.h"
#include "serialization/rainforest/deviceenergyusage_serializer.h"

using namespace Rainforest;

DeviceEnergyUsage::DeviceEnergyUsage() :
	TotalDelivered(0, 0, 0, 0, 0, false),
	TotalReceived(0, 0, 0, 0, 0, false),
	Now(0, 0, 0, 0, 0, false),
	History(HISTORY_DURATION)
{
}

DeviceEnergyUsage::~DeviceEnergyUsage()
{
}

boost::json::object DeviceEnergyUsage::Serialize() const
{
	return DeviceEnergyUsage_Serializer(*this).Serialize();
}

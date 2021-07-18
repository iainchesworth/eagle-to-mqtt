#include "metering/devices/fronius/common/device_stats.h"
#include "serialization/fronius/devicestatistics_serializer.h"

using namespace Fronius;

DeviceStatistics::DeviceStatistics() :
	ISerializable()
{
}

boost::json::object DeviceStatistics::Serialize() const
{
	return DeviceStatistics_Serializer(*this).Serialize();
}

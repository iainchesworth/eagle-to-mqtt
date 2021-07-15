#include "metering/devices/rainforest/common/device_stats.h"
#include "serialization/rainforest/devicestatistics_serializer.h"

using namespace Rainforest;

DeviceStatistics::DeviceStatistics() :
	ISerializable()
{
}

DeviceStatistics::~DeviceStatistics()
{
}

boost::json::object DeviceStatistics::Serialize() const
{
	return DeviceStatistics_Serializer(*this).Serialize();
}

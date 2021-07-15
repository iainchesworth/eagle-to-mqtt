#include "metering/devices/rainforest/common/device_connectivity.h"
#include "serialization/rainforest/deviceconnectivity_serializer.h"

using namespace Rainforest;

DeviceConnectivity::DeviceConnectivity() :
	Status(Statuses::StatusTypes::Unknown),
	Channel(),
	LinkStrength()
{
}

DeviceConnectivity::~DeviceConnectivity()
{
}

boost::json::object DeviceConnectivity::Serialize() const
{
	return DeviceConnectivity_Serializer(*this).Serialize();
}

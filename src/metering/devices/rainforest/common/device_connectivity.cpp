#include "metering/devices/rainforest/common/device_connectivity.h"
#include "serialization/rainforest/deviceconnectivity_serializer.h"

using namespace Rainforest;

DeviceConnectivity::DeviceConnectivity() :
	LinkStrength()
{
}

boost::json::object DeviceConnectivity::Serialize() const
{
	return DeviceConnectivity_Serializer(*this).Serialize();
}

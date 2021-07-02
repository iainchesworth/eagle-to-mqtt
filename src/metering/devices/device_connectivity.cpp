#include "metering/devices/device_connectivity.h"

DeviceConnectivity::DeviceConnectivity() :
	Status(Statuses::StatusTypes::Unknown),
	Channel(),
	LinkStrength()
{
}

DeviceConnectivity::~DeviceConnectivity()
{
}

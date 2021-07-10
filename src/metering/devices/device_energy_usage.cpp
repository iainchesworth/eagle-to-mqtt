#include "metering/devices/device_energy_usage.h"

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
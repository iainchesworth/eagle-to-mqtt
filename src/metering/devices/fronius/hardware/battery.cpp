#include "metering/devices/fronius/hardware/battery.h"

Battery::Battery(bool is_installed) :
	HardwareBase(is_installed)
{
}

std::string Battery::DeviceType() const
{
	static const std::string DEVICE_TYPE{ "Battery" };
	return DEVICE_TYPE;
}

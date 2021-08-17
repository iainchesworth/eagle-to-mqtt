#include "metering/devices/fronius/hardware/inverter.h"

Inverter::Inverter(bool is_installed) :
	HardwareBase(is_installed)
{
}

std::string Inverter::DeviceType() const
{
	static const std::string DEVICE_TYPE{ "Inverter" };
	return DEVICE_TYPE;
}

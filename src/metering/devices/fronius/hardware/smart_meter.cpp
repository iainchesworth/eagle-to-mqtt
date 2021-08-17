#include "metering/devices/fronius/hardware/smart_meter.h"

SmartMeter::SmartMeter(bool is_installed) :
	HardwareBase(is_installed)
{
}

std::string SmartMeter::DeviceType() const
{
	static const std::string DEVICE_TYPE{ "Smart Meter" };
	return DEVICE_TYPE;
}

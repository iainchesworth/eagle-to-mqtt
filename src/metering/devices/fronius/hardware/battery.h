#ifndef BATTERY_H
#define BATTERY_H

#include "metering/devices/fronius/hardware/hardware.h"

class Battery : public HardwareBase
{
public:
	Battery(bool is_installed);

private:
	std::string DeviceType() const final;
};

#endif // BATTERY_H

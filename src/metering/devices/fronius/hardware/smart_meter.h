#ifndef SMARTMETER_H
#define SMARTMETER_H

#include "metering/devices/fronius/hardware/hardware.h"

class SmartMeter : public HardwareBase
{
public:
	SmartMeter(bool is_installed);

private:
	std::string DeviceType() const final;
};

#endif // SMARTMETER_H

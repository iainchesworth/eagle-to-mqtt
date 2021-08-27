#ifndef INVERTER_H
#define INVERTER_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/hardware/hardware.h"

class Inverter : public HardwareBase
{
public:
	Inverter(bool is_installed);

private:
	std::string DeviceType() const final;
};

#endif // INVERTER_H

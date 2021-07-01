#ifndef DEVICEENERGYUSAGE_SERIALIZER_H
#define DEVICEENERGYUSAGE_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/device_energy_usage.h"

class DeviceEnergyUsage_Serializer : public ISerializer
{
public:
	DeviceEnergyUsage_Serializer(std::shared_ptr<DeviceEnergyUsage> deu_ptr);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // DEVICEENERGYUSAGE_SERIALIZER_H

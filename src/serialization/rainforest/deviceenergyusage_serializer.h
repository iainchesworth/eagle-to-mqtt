#ifndef RAINFOREST_DEVICEENERGYUSAGE_SERIALIZER_H
#define RAINFOREST_DEVICEENERGYUSAGE_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/rainforest/common/device_energy_usage.h"

namespace Rainforest
{

class DeviceEnergyUsage_Serializer : public ISerializer<DeviceEnergyUsage>
{
public:
	explicit DeviceEnergyUsage_Serializer(const DeviceEnergyUsage& deu);

public:
	boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICEENERGYUSAGE_SERIALIZER_H

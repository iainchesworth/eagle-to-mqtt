#ifndef DEVICE_ENERGY_USAGE_H
#define DEVICE_ENERGY_USAGE_H

#include <map>

#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/demand.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"

// Forward declarations
class DeviceEnergyUsage_Serializer;

class DeviceEnergyUsage : public ISerializable
{
public:
	DeviceEnergyUsage();
	virtual ~DeviceEnergyUsage();

public:
	Summation TotalDelivered;
	Summation TotalReceived;

public:
	Demand Now;
	std::map<timepoint_from_jan2000, Demand> History;

public:
	friend class DeviceStatistics_Serializer;
};

#endif // DEVICE_ENERGY_USAGE_H

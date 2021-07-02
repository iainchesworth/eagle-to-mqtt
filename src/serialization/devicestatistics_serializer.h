#ifndef DEVICESTATISTICS_SERIALIZER_H
#define DEVICESTATISTICS_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/device_stats.h"

class DeviceStatistics_Serializer : public ISerializer
{
public:
	DeviceStatistics_Serializer(std::shared_ptr<DeviceStatistics> ds_ptr);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // DEVICESTATISTICS_SERIALIZER_H

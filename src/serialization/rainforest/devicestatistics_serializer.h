#ifndef RAINFOREST_DEVICESTATISTICS_SERIALIZER_H
#define RAINFOREST_DEVICESTATISTICS_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/rainforest/common/device_stats.h"

namespace Rainforest
{

class DeviceStatistics_Serializer : public ISerializer<DeviceStatistics>
{
public:
	DeviceStatistics_Serializer(const DeviceStatistics& ds);

public:
	virtual boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICESTATISTICS_SERIALIZER_H

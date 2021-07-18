#ifndef FRONIUS_DEVICESTATISTICS_SERIALIZER_H
#define FRONIUS_DEVICESTATISTICS_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/fronius/common/device_stats.h"

namespace Fronius
{

class DeviceStatistics_Serializer : public ISerializer<DeviceStatistics>
{
public:
	explicit DeviceStatistics_Serializer(const DeviceStatistics& ds);

public:
	virtual boost::json::object Serialize() const final;
};

}
// namespace Fronius

#endif // FRONIUS_DEVICESTATISTICS_SERIALIZER_H

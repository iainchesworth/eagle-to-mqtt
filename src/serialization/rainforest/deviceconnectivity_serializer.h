#ifndef RAINFOREST_DEVICECONNECTIVITY_SERIALIZER_H
#define RAINFOREST_DEVICECONNECTIVITY_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/rainforest/common/device_connectivity.h"

namespace Rainforest
{

class DeviceConnectivity_Serializer : public ISerializer<DeviceConnectivity>
{
public:
	DeviceConnectivity_Serializer(const DeviceConnectivity& dc);

public:
	virtual boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICECONNECTIVITY_SERIALIZER_H

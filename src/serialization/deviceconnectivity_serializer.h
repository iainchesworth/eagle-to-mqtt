#ifndef DEVICECONNECTIVITY_SERIALIZER_H
#define DEVICECONNECTIVITY_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/device_connectivity.h"

class DeviceConnectivity_Serializer : public ISerializer
{
public:
	DeviceConnectivity_Serializer(std::shared_ptr<DeviceConnectivity> dc_ptr);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // DEVICECONNECTIVITY_SERIALIZER_H

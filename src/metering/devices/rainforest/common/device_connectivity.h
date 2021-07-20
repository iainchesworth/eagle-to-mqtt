#ifndef RAINFOREST_DEVICE_CONNECTIVITY_H
#define RAINFOREST_DEVICE_CONNECTIVITY_H

#include <cstdint>
#include <string>

#include "interfaces/iserializable.h"
#include "metering/common/statuses.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

namespace Rainforest
{

class DeviceConnectivity : public ISerializable
{
public:
	DeviceConnectivity();
	virtual ~DeviceConnectivity() = default;

public:
	struct
	{
		ZigBeeMacId Eagle_MacId;		// Zigbee MAC id of the Eagle device connected to the meter (and talking to us)
		ZigBeeMacId Meter_MacId;		// Also termed the "coordinator" in Zigbee parlance; "CoordMacId" in V1 payloads
		ZigBeeMacId Extended_PanId;		// ????
	}
	ZigBee;

public:
	Statuses Status{ Statuses::StatusTypes::Unknown };

public:
	std::string Channel;
	uint8_t LinkStrength;

public:
	boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICE_CONNECTIVITY_H

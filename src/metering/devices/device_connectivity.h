#ifndef DEVICE_CONNECTIVITY_H
#define DEVICE_CONNECTIVITY_H

#include <cstdint>
#include <string>

#include "interfaces/iserializable.h"
#include "metering/common/statuses.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

// Forward declarations
class DeviceConnectivity_Serializer;

class DeviceConnectivity : public ISerializable
{
public:
	DeviceConnectivity();
	virtual ~DeviceConnectivity();

public:
	struct
	{
		ZigBeeMacId Eagle_MacId;		// Zigbee MAC id of the Eagle device connected to the meter (and talking to us)
		ZigBeeMacId Meter_MacId;		// Also termed the "coordinator" in Zigbee parlance; "CoordMacId" in V1 payloads
		ZigBeeMacId Extended_PanId;		// ????
	}
	ZigBee;

public:
	Statuses Status;

public:
	std::string Channel;
	uint8_t LinkStrength;

public:
	friend class DeviceConnectivity_Serializer;
};

#endif // DEVICE_CONNECTIVITY_H

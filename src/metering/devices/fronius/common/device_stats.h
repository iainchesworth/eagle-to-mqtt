#ifndef FRONIUS_DEVICE_STATS_H
#define FRONIUS_DEVICE_STATS_H

#include <boost/json.hpp>

#include <cstdint>

#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"

namespace Fronius
{

class DeviceStatistics : public ISerializable
{
public:
	DeviceStatistics();

public:
	UnixTimepoint LastMessageTimestamp;

	// Generic statistics
	uint64_t MessageCount;

	// Errors and other problems
	uint64_t MissingPayloadFields;
	uint64_t ErrorsWhileProcessing;

	// Payload types
	uint64_t SolarAPI_CurrentData_InverterCount;
	uint64_t SolarAPI_CurrentData_SensorCardCount;
	uint64_t SolarAPI_CurrentData_StringControlCount;
	uint64_t SolarAPI_CurrentData_MeterCount;
	uint64_t SolarAPI_CurrentData_PowerFlowCount;
	uint64_t SolarAPI_LogData_DataCount;
	uint64_t SolarAPI_LogData_ErrorsAndEventsCount;
	uint64_t UnknownMessageCount;

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Fronius

#endif // FRONIUS_DEVICE_STATS_H

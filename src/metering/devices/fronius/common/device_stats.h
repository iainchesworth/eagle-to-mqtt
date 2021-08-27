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
	UnixTimepoint LastMessageTimestamp{};

	// Generic statistics
	uint64_t TotalMessageCount{ 0 };

	// Errors and other problems
	uint64_t MissingPayloadFields{ 0 };
	uint64_t ErrorsWhileProcessing{ 0 };

	// Payload types
	uint64_t SolarAPI_CurrentData_InverterCount{ 0 };
	uint64_t SolarAPI_CurrentData_SensorCardCount{ 0 };
	uint64_t SolarAPI_CurrentData_StringControlCount{ 0 };
	uint64_t SolarAPI_CurrentData_MeterCount{ 0 };
	uint64_t SolarAPI_CurrentData_PowerFlowCount{ 0 };
	uint64_t SolarAPI_LogData_DataCount{ 0 };
	uint64_t SolarAPI_LogData_ErrorsAndEventsCount{ 0 };
	uint64_t UnknownMessageCount{ 0 };

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Fronius

#endif // FRONIUS_DEVICE_STATS_H

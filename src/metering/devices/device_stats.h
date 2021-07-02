#ifndef DEVICE_STATS_H
#define DEVICE_STATS_H

#include <cstdint>

#include "exceptions/not_implemented.h"
#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"

// Forward declarations
class DeviceStatistics_Serializer;

struct DeviceStatistics : public ISerializable
{
public:
	timepoint_from_epoch LastMessageTimestamp;

	// Generic statistics
	uint64_t MessageCount;

	// Errors and other problems
	uint64_t MissingPayloadFields;
	uint64_t ErrorsWhileProcessing;

	// Payload types
	uint64_t BillingPeriodCount;
	uint64_t BlockPriceDetailCount;
	uint64_t ConnectionStatusCount;
	uint64_t CurrentSummationCount;
	uint64_t DeviceInfoCount;
	uint64_t InstantaneousDemandCount;
	uint64_t MessageClusterCount;
	uint64_t NetworkInfoCount;
	uint64_t PriceClusterCount;
	uint64_t TimeClusterCount;
	uint64_t UnknownMessageCount;

public:
	friend class DeviceStatistics_Serializer;
};

#endif // DEVICE_STATS_H

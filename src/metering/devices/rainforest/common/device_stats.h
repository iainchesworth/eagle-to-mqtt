#ifndef RAINFOREST_DEVICE_STATS_H
#define RAINFOREST_DEVICE_STATS_H

#include <boost/json.hpp>

#include <cstdint>

#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"

namespace Rainforest
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
	virtual boost::json::object Serialize() const;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICE_STATS_H

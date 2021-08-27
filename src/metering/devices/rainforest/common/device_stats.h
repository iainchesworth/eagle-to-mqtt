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
	UnixTimepoint LastMessageTimestamp{};

	// Generic statistics
	uint64_t TotalMessageCount{ 0 };

	// Errors and other problems
	uint64_t MissingPayloadFields{ 0 };
	uint64_t ErrorsWhileProcessing{ 0 };

	// Payload types
	uint64_t BillingPeriodCount{ 0 };
	uint64_t BlockPriceDetailCount{ 0 };
	uint64_t ConnectionStatusCount{ 0 };
	uint64_t CurrentSummationCount{ 0 };
	uint64_t DeviceInfoCount{ 0 };
	uint64_t InstantaneousDemandCount{ 0 };
	uint64_t MessageClusterCount{ 0 };
	uint64_t NetworkInfoCount{ 0 };
	uint64_t PriceClusterCount{ 0 };
	uint64_t TimeClusterCount{ 0 };
	uint64_t UnknownMessageCount{ 0 };

public:
	boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICE_STATS_H

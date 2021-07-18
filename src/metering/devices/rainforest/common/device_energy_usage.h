#ifndef RAINFOREST_DEVICE_ENERGY_USAGE_H
#define RAINFOREST_DEVICE_ENERGY_USAGE_H

#include <boost/circular_buffer.hpp>

#include <utility>

#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/demand.h"
#include "metering/devices/rainforest/messages/partial_message_types/summation.h"

namespace Rainforest
{

class DeviceEnergyUsage : public ISerializable
{
	static constexpr uint32_t HISTORY_DURATION{ (24 * 60 * 60) / 8 };

public:
	DeviceEnergyUsage();

public:
	Summation TotalDelivered;
	Summation TotalReceived;

public:
	Demand Now;

public:
	using HistoryElement = std::pair<ZigbeeTimepoint, Demand>;
	using HistoryBuffer = boost::circular_buffer<HistoryElement>;
	HistoryBuffer History;

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICE_ENERGY_USAGE_H

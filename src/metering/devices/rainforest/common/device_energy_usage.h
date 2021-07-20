#ifndef RAINFOREST_DEVICE_ENERGY_USAGE_H
#define RAINFOREST_DEVICE_ENERGY_USAGE_H

#include <boost/circular_buffer.hpp>

#include <utility>

#include "interfaces/iserializable.h"
#include "metering/common/energy_value.h"
#include "metering/common/timestamps.h"

namespace Rainforest
{

class DeviceEnergyUsage : public ISerializable
{
	static constexpr uint32_t HISTORY_DURATION{ (24 * 60 * 60) / 8 };

public:
	DeviceEnergyUsage();

public:
	Usage TotalDelivered{ 0, 0, 0, 0, 0, false };
	Usage TotalReceived{ 0, 0, 0, 0, 0, false };

public:
	Power Now{ 0, 0, 0, 0, 0, false };

public:
	using HistoryElement = std::pair<ZigbeeTimepoint, Power>;
	using HistoryBuffer = boost::circular_buffer<HistoryElement>;
	HistoryBuffer History{ HISTORY_DURATION };

public:
	boost::json::object Serialize() const final;
};

}
// namespace Rainforest

#endif // RAINFOREST_DEVICE_ENERGY_USAGE_H

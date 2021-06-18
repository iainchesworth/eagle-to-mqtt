#ifndef INSTANTANEOUS_DEMAND_H
#define INSTANTANEOUS_DEMAND_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/demand_in_watts.h"
#include "metering/common/protocol_types.h"
#include "metering/common/zigbee_mac_id.h"

class InstantaneousDemand : public IFragmentProcessor
{
public:
	InstantaneousDemand(const boost::property_tree::ptree& node);

private:
	ZigBeeMacId m_DeviceMacId;
	std::string m_MeterMacId;
	std::chrono::time_point<std::chrono::system_clock> m_TimeStamp;
	DemandInWatts m_Demand;
	ProtocolTypes m_Protocol;
};

#endif // INSTANTANEOUS_DEMAND_H

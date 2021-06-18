#ifndef CURRENT_SUMMATION_H
#define CURRENT_SUMMATION_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/protocol_types.h"
#include "metering/common/zigbee_mac_id.h"

class CurrentSummation : public IFragmentProcessor
{
public:
	CurrentSummation(const boost::property_tree::ptree& node);

private:
	ZigBeeMacId m_DeviceMacId;
	ZigBeeMacId m_MeterMacId;
	std::chrono::time_point<std::chrono::system_clock> m_TimeStamp;
	double m_SummationDelivered;
	double m_SummationReceived;
	ProtocolTypes m_Protocol;
};

#endif // CURRENT_SUMMATION_H

#ifndef CURRENT_SUMMATION_H
#define CURRENT_SUMMATION_H

#include <boost/property_tree/ptree.hpp>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class CurrentSummation : public IFragmentProcessor
{
public:
	CurrentSummation(const boost::property_tree::ptree& node);
	virtual ~CurrentSummation();

public:
	Summation Delivered() const;
	Summation Received() const;

private:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_TimeStamp;
	Summation m_SummationDelivered;
	Summation m_SummationReceived;
};

#endif // CURRENT_SUMMATION_H

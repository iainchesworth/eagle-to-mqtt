#ifndef INSTANTANEOUS_DEMAND_H
#define INSTANTANEOUS_DEMAND_H

#include <boost/property_tree/ptree.hpp>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/demand.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class InstantaneousDemand : public IFragmentProcessor
{
public:
	InstantaneousDemand(const boost::property_tree::ptree& node);
	virtual ~InstantaneousDemand();

public:
	Demand Now() const;
	timepoint_from_jan2000 Timestamp() const;

private:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_Timestamp;
	Demand m_Demand;
};

#endif // INSTANTANEOUS_DEMAND_H

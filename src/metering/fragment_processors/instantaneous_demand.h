#ifndef INSTANTANEOUS_DEMAND_H
#define INSTANTANEOUS_DEMAND_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/demand.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class InstantaneousDemand : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;

public:
	InstantaneousDemand(const boost::property_tree::ptree& node);
	virtual ~InstantaneousDemand();

public:
	Demand Now() const;
	ZigbeeTimepoint Timestamp() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	ZigbeeTimepoint m_Timestamp;
	Demand m_Demand;
};

#endif // INSTANTANEOUS_DEMAND_H

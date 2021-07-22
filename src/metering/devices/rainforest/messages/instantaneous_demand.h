#ifndef INSTANTANEOUS_DEMAND_H
#define INSTANTANEOUS_DEMAND_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/energy_value.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class InstantaneousDemand : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP; 
	static const std::string FIELDNAME_DEMAND;

public:
	explicit InstantaneousDemand(const boost::property_tree::ptree& node);
	virtual ~InstantaneousDemand() = default;

public:
	Power Now() const;
	ZigbeeTimepoint Timestamp() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	ZigbeeTimepoint m_Timestamp;
	Power m_Demand;
};

#endif // INSTANTANEOUS_DEMAND_H

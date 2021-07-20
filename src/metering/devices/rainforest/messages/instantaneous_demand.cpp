#include <string>

#include "metering/common/unit_converters.h"
#include "metering/devices/rainforest/messages/instantaneous_demand.h"
#include "metering/types/optional.h"

const std::string InstantaneousDemand::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string InstantaneousDemand::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string InstantaneousDemand::FIELDNAME_DEMAND{ "Demand" };

InstantaneousDemand::InstantaneousDemand(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(IsEssential<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
	m_Demand(Energy::ExtractFromPayload<Power>(node, FIELDNAME_DEMAND))
{
}

Power InstantaneousDemand::Now() const
{
	return m_Demand;
}

ZigbeeTimepoint InstantaneousDemand::Timestamp() const
{
	return m_Timestamp;
}

#include <string>

#include "metering/common/unit_converters.h"
#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/type_handlers/optional.h"

const std::string InstantaneousDemand::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string InstantaneousDemand::FIELDNAME_TIMESTAMP{ "TimeStamp" };

InstantaneousDemand::InstantaneousDemand(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>(FIELDNAME_TIMESTAMP))),
	m_Demand(Demand::ExtractFromPayload(node))
{
}

InstantaneousDemand::~InstantaneousDemand()
{
}

Demand InstantaneousDemand::Now() const
{
	return m_Demand;
}

timepoint_from_jan2000 InstantaneousDemand::Timestamp() const
{
	return m_Timestamp;
}

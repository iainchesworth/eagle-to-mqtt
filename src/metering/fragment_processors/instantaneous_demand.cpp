#include <string>

#include "metering/common/unit_converters.h"
#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/type_handlers/essential.h"

InstantaneousDemand::InstantaneousDemand(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
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

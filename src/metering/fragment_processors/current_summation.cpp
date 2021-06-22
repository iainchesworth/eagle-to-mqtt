#include <string>

#include "metering/fragment_processors/current_summation.h"
#include "metering/common/unit_converters.h"
#include "metering/type_handlers/essential.h"

CurrentSummation::CurrentSummation(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_TimeStamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
	m_SummationDelivered(Summation::ExtractFromPayload(node, "SummationDelivered")),
	m_SummationReceived(Summation::ExtractFromPayload(node, "SummationReceived"))
{
}

CurrentSummation::~CurrentSummation()
{
}

Summation CurrentSummation::Delivered() const
{
	return m_SummationDelivered;
}

Summation CurrentSummation::Received() const
{
	return m_SummationReceived;
}

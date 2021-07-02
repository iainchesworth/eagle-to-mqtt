#include <string>

#include "metering/fragment_processors/current_summation.h"
#include "metering/common/unit_converters.h"
#include "metering/type_handlers/optional.h"

const std::string CurrentSummation::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string CurrentSummation::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string CurrentSummation::FIELDNAME_SUMMATIONDELIVERED{ "SummationDelivered" };
const std::string CurrentSummation::FIELDNAME_SUMMATIONRECEIVED{ "SummationReceived" };

CurrentSummation::CurrentSummation(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_TimeStamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>(FIELDNAME_TIMESTAMP))),
	m_SummationDelivered(IsOptional<Summation>(node, FIELDNAME_SUMMATIONDELIVERED)),
	m_SummationReceived(IsOptional<Summation>(node, FIELDNAME_SUMMATIONRECEIVED))
{
}

CurrentSummation::~CurrentSummation()
{
}

std::optional<Summation> CurrentSummation::Delivered() const
{
	return m_SummationDelivered;
}

std::optional<Summation> CurrentSummation::Received() const
{
	return m_SummationReceived;
}

#include <string>

#include "metering/common/unit_converters.h"
#include "metering/devices/rainforest/messages/current_summation.h"
#include "metering/types/optional.h"

const std::string CurrentSummation::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string CurrentSummation::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string CurrentSummation::FIELDNAME_SUMMATIONDELIVERED{ "SummationDelivered" };
const std::string CurrentSummation::FIELDNAME_SUMMATIONRECEIVED{ "SummationReceived" };

CurrentSummation::CurrentSummation(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_TimeStamp(IsOptional<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
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

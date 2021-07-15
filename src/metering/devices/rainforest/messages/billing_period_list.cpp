#include "metering/devices/rainforest/messages/billing_period_list.h"
#include "metering/types/integer.h"
#include "metering/types/optional.h"

const std::string BillingPeriodList::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string BillingPeriodList::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string BillingPeriodList::FIELDNAME_NUMBEROFPERIODS{ "NumberOfPeriods" };
const std::string BillingPeriodList::FIELDNAME_CURRENTSTART{ "CurrentStart" };
const std::string BillingPeriodList::FIELDNAME_CURRENTDURATION{ "CurrentDuration" };

BillingPeriodList::BillingPeriodList(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(IsOptional<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
	m_NumberOfPeriods(IsOptionalWithDefault<uint8_t>(node, FIELDNAME_NUMBEROFPERIODS, 0)),
	m_Start(),
	m_Duration()
{
	auto current_start = IsOptionalWithDefault<std::string>(node, FIELDNAME_CURRENTSTART, "0x00000000");
	auto current_duration = IsOptionalWithDefault<std::string>(node, FIELDNAME_CURRENTDURATION, "0x00000000");

	auto offset = unsigned_to_signed(hex_string_to_uint32_t(current_start));				   // Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto start_time_as_time_point = now + std::chrono::duration<int64_t>(offset);
	auto duration_in_minutes = std::chrono::minutes(hex_string_to_uint32_t(current_duration)); // Will default to a duration of "0" if not present.

	m_Start = start_time_as_time_point;
	m_Duration = duration_in_minutes;
}

BillingPeriodList::~BillingPeriodList()
{
}

std::chrono::time_point<std::chrono::system_clock> BillingPeriodList::CurrentPeriodStart() const
{
	return m_Start;
}

std::chrono::time_point<std::chrono::system_clock> BillingPeriodList::CurrentPeriodEnd() const
{
	return m_Start + m_Duration;
}

uint8_t BillingPeriodList::NumberOfPeriods() const
{
	return m_NumberOfPeriods;
}

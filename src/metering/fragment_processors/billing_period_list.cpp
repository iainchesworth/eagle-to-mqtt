#include "metering/fragment_processors/billing_period_list.h"
#include "metering/type_handlers/expected.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

BillingPeriodList::BillingPeriodList(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsExpected<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
	m_NumberOfPeriods(),
	m_Start(),
	m_Duration()
{
	auto current_start = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("CurrentStart"); }, "0x00000000");
	auto current_duration = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("CurrentDuration"); }, "0x00000000");

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

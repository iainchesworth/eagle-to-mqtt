#include "metering/fragment_processors/partial_fragment_types/block_period.h"
#include "metering/type_handlers/boolean.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/expected.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

BlockPeriod::BlockPeriod(double consumption, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration) :
	m_Consumption(consumption),
	m_Start(start_time),
	m_Duration(duration)
{
}

std::chrono::time_point<std::chrono::system_clock> BlockPeriod::Starts() const
{
	return m_Start;
}

std::chrono::time_point<std::chrono::system_clock> BlockPeriod::Ends() const
{
	return m_Start + m_Duration;
}

double BlockPeriod::Consumption() const
{
	return m_Consumption;
}

BlockPeriod BlockPeriod::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	auto current_start = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("CurrentStart"); }, "0x00000000");  // Does not exist in V1 payloads
	auto current_duration = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("CurrentDuration"); }, "0x0000");		   // Does not exist in V1 payloads

	auto offset = unsigned_to_signed(hex_string_to_uint32_t(current_start));				   // Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto start_time_as_time_point = now + std::chrono::duration<int64_t>(offset);
	auto duration_in_minutes = std::chrono::minutes(hex_string_to_uint16_t(current_duration)); // Will default to a duration of "0" if not present.

	double consumption = IsOptional<uint64_t>([&node]() -> uint64_t { return GetValue_UInt64(node, "BlockPeriodConsumption"); });
	auto consumption_muliplier = IsOptional<uint32_t>([&node]() -> uint32_t { return GetValue_UInt32(node, "BlockPeriodConsumptionMultiplier"); });
	auto consumption_divisor = IsOptional<uint32_t>([&node]() -> uint32_t { return GetValue_UInt32(node, "BlockPeriodConsumptionDivisor"); });

	consumption *= (0 == consumption_muliplier) ? 1 : consumption_muliplier;
	consumption /= (0 == consumption_divisor) ? 1 : consumption_divisor;

	return BlockPeriod(consumption, start_time_as_time_point, duration_in_minutes);
}

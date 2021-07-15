#include "metering/devices/rainforest/messages/partial_message_types/block_period.h"
#include "metering/types/boolean.h"
#include "metering/types/essential.h"
#include "metering/types/integer.h"
#include "metering/types/optional.h"

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
	auto current_start = IsOptionalWithDefault<uint32_t>(node, "CurrentStart", 0);		 // Does not exist in V1 payloads
	auto current_duration = IsOptionalWithDefault<uint16_t>(node, "CurrentDuration", 0); // Does not exist in V1 payloads

	auto duration_in_minutes = std::chrono::minutes(current_duration);		// Will default to a duration of "0" if not present.
	auto offset = unsigned_to_signed(current_start);						// Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto start_time_as_time_point = now + std::chrono::duration<int64_t>(offset);
	
	double consumption = IsOptionalWithDefault<uint64_t>(node, "BlockPeriodConsumption", 0);
	auto consumption_muliplier = IsOptionalWithDefault<uint32_t>(node, "BlockPeriodConsumptionMultiplier", 0);
	auto consumption_divisor = IsOptionalWithDefault<uint32_t>(node, "BlockPeriodConsumptionDivisor", 0);

	consumption *= (0 == consumption_muliplier) ? 1 : consumption_muliplier;
	consumption /= (0 == consumption_divisor) ? 1 : consumption_divisor;

	return BlockPeriod(consumption, start_time_as_time_point, duration_in_minutes);
}

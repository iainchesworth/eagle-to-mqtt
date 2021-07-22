#include "metering/common/unit_converters.h"
#include "metering/devices/rainforest/messages/partial_message_types/pricing_tier.h"
#include "metering/types/essential.h"
#include "metering/types/optional.h"

PricingTier::PricingTier(const std::string& rate_label, const PricingInfo price_info, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration) :
	m_RateLabel(rate_label),
	m_PricingInfo(price_info),
	m_StartTime(start_time),
	m_Duration(duration)
{
}

std::string PricingTier::RateLabel() const
{
	return m_RateLabel;
}

PricingInfo PricingTier::Pricing() const
{
	return m_PricingInfo;
}

std::chrono::time_point<std::chrono::system_clock> PricingTier::StartsAt() const
{
	return m_StartTime;
}

std::chrono::time_point<std::chrono::system_clock> PricingTier::EndsAt() const
{
	return m_StartTime + m_Duration;
}

PricingTier PricingTier::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	auto rate_label = IsOptionalWithDefault<std::string>(node, "RateLabel", "");			// Optionally present in V1 and V2 payloads
	auto tier_label = IsOptionalWithDefault<std::string>(node, "TierLabel", "");			// Optionally present in V1 payloads (note: precludes RateLabel)

	auto start_time = IsOptionalWithDefault<uint32_t>(node, "StartTime", 0);  // Does not exist in V1 payloads
	auto duration = IsOptionalWithDefault<uint16_t>(node, "Duration", 0);	  // Does not exist in V1 payloads

	std::string label;

	if ((0 != rate_label.length()) && (0 != tier_label.length()))
	{
		// Default to using the "RateLabel" over "TierLabel" when both are present.
		label = rate_label;
	} 
	else if (0 != rate_label.length())
	{
		label = rate_label;
	}
	else if (0 != tier_label.length())
	{
		label = tier_label;
	}
	else
	{
		// Neither the tier nor the rate labels are present.
	}

	auto dur = std::chrono::minutes(duration);	  // Will default to a duration of "0" if not present.
	auto offset = unsigned_to_signed(start_time); // Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto tp = now + std::chrono::duration<int64_t>(offset);

	return PricingTier(label, PricingInfo::ExtractFromPayload(node), tp, dur);	
}

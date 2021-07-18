#ifndef PRICING_TIER_H
#define PRICING_TIER_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <map>
#include <string>

#include "metering/common/tiers.h"
#include "metering/devices/rainforest/messages/partial_message_types/pricing_info.h"

class PricingTier
{
public:
	PricingTier(std::string rate_label, const PricingInfo price_info, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration);

public:
	std::string RateLabel() const;
	PricingInfo Pricing() const;
	std::chrono::time_point<std::chrono::system_clock> StartsAt() const;
	std::chrono::time_point<std::chrono::system_clock> EndsAt() const;

private:
	std::string m_RateLabel;
	PricingInfo m_PricingInfo;
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::minutes m_Duration;

public:
	static PricingTier ExtractFromPayload(const boost::property_tree::ptree& node);
};

using PricingTiers = std::map<Tiers, PricingTier>;

#endif // PRICING_TIER_H

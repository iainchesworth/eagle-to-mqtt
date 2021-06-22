#ifndef INVALID_PRICING_TIER_VALUE_H
#define INVALID_PRICING_TIER_VALUE_H

#include <stdexcept>
#include <string>

class InvalidPricingTierValue : public std::runtime_error
{
public:
	InvalidPricingTierValue(std::string reason_for_invalid_value);
};

#endif // INVALID_PRICING_TIER_VALUE_H

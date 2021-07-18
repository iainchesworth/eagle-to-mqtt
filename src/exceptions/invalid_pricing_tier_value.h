#ifndef INVALID_PRICING_TIER_VALUE_H
#define INVALID_PRICING_TIER_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidPricingTierValue : public InvalidValue
{
public:
	InvalidPricingTierValue(const std::string& reason_for_invalid_value);
};

#endif // INVALID_PRICING_TIER_VALUE_H

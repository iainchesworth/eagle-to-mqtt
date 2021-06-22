#include "exceptions/invalid_pricing_tier_value.h"

InvalidPricingTierValue::InvalidPricingTierValue(std::string reason_for_invalid_value) :
	std::runtime_error(reason_for_invalid_value)
{
}

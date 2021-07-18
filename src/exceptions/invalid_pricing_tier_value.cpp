#include "exceptions/invalid_pricing_tier_value.h"

InvalidPricingTierValue::InvalidPricingTierValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

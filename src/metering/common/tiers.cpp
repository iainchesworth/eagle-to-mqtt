#include <boost/log/trivial.hpp>

#include "exceptions/invalid_pricing_tier_value.h"
#include "metering/common/tiers.h"
#include "metering/common/unit_converters.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/integer.h"

const std::string Tiers::NOT_SPECIFIED{ "Not Specified" };
const std::string Tiers::TIER_1{ "Tier 1" };
const std::string Tiers::TIER_2{ "Tier 2" };
const std::string Tiers::TIER_3{ "Tier 3" };
const std::string Tiers::TIER_4{ "Tier 4" };
const std::string Tiers::TIER_5{ "Tier 5" };
const std::string Tiers::UNKNOWN{ "Unknown" };

Tiers::Tiers() :
	Tiers(SupportedTiers::NotSpecified)
{
}

Tiers::Tiers(SupportedTiers pricing_tier) :
	m_PricingTier(pricing_tier)
{
}

Tiers::Tiers(const std::string& pricing_tier_string) :
	m_PricingTier(FromString(pricing_tier_string))
{
}

Tiers::SupportedTiers Tiers::FromString(const std::string& pricing_tier_string)
{
	const uint32_t V1_LENGTH_A = 1;
	const uint32_t V1_LENGTH_B = 2;
	const uint32_t V2_LENGTH = 4;

	uint8_t tier_as_int;

	switch (pricing_tier_string.length())
	{
	case V1_LENGTH_A:	// Format: '1'
	case V1_LENGTH_B:	// Format: '12'
		tier_as_int = hex_string_to_uint8_t(pricing_tier_string);
		break;

	case V2_LENGTH:		// Format: '0x12'
		tier_as_int = std::stoul(pricing_tier_string, nullptr, 16);
		break;

	default:
		BOOST_LOG_TRIVIAL(warning) << L"Unknown string value provided for pricing tier";
		throw InvalidPricingTierValue("Pricing tier value has invalid length - expected 1, 2 or 4, got " + std::to_string(pricing_tier_string.length()));
	}

	SupportedTiers tier;

	switch (tier_as_int) // Cannot cast as casting from a non-valid enum <value> is UD
	{
	case 1: tier = SupportedTiers::Tier_1; break;
	case 2: tier = SupportedTiers::Tier_2; break;
	case 3: tier = SupportedTiers::Tier_3; break;
	case 4: tier = SupportedTiers::Tier_4; break;
	case 5: tier = SupportedTiers::Tier_5; break;

	default:
		BOOST_LOG_TRIVIAL(warning) << L"Unknown pricing tier provided to converter: " << pricing_tier_string;
		tier = SupportedTiers::Unknown;
		break;
	}

	return tier;
}

std::string Tiers::ToString(const SupportedTiers pricing_tier)
{
	switch (pricing_tier)
	{
	case SupportedTiers::NotSpecified:
		return NOT_SPECIFIED;
	case SupportedTiers::Tier_1:
		return TIER_1;
	case SupportedTiers::Tier_2:
		return TIER_2;
	case SupportedTiers::Tier_3:
		return TIER_3;
	case SupportedTiers::Tier_4:
		return TIER_4;
	case SupportedTiers::Tier_5:
		return TIER_5;
	case SupportedTiers::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Tiers::operator==(const Tiers& other) const
{
	return (m_PricingTier == other.m_PricingTier);
}

std::ostream& operator<<(std::ostream& os, const Tiers& pricing_tier)
{
	os << pricing_tier.ToString(pricing_tier.m_PricingTier);
	return os;
}

bool operator<(const Tiers& lhs, const Tiers& rhs)
{
	return (lhs.m_PricingTier < rhs.m_PricingTier);
}

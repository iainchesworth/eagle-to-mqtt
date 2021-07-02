#ifndef TIERS_H
#define TIERS_H

#include <ostream>
#include <string>

class Tiers
{
	static const std::string NOT_SPECIFIED;
	static const std::string TIER_1;
	static const std::string TIER_2;
	static const std::string TIER_3;
	static const std::string TIER_4;
	static const std::string TIER_5;
	static const std::string UNKNOWN;

public:
	enum class SupportedTiers
	{
		NotSpecified,
		Tier_1 = 1,
		Tier_2 = 2,
		Tier_3 = 3,
		Tier_4 = 4,
		Tier_5 = 5,
		Unknown
	};

public:
	Tiers();
	Tiers(SupportedTiers pricing_tier);
	Tiers(const std::string& pricing_tier);

private:
	SupportedTiers m_PricingTier;

public:
	static SupportedTiers FromString(const std::string& pricing_tier_string);
	static std::string ToString(const SupportedTiers pricing_tier);

public:
	bool operator==(const Tiers& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Tiers& pricing_tier);
	friend bool operator< (const Tiers& lhs, const Tiers& rhs);
};

#endif // TIERS_H

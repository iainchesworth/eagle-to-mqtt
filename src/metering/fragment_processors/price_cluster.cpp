#include "metering/common/unit_converters.h"
#include "metering/fragment_processors/price_cluster.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/expected.h"

PriceCluster::PriceCluster(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsExpected<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
	m_Tier(IsEssential<Tiers>([&node]() -> Tiers { return Tiers::FromString(node.get<std::string>("Tier")); })),
	m_TierPricing(PricingTier::ExtractFromPayload(node))
{
}

PriceCluster::~PriceCluster()
{
}

Tiers PriceCluster::Tier() const
{
	return m_Tier;
}

PricingTier PriceCluster::TierPricing() const
{
	return m_TierPricing;
}

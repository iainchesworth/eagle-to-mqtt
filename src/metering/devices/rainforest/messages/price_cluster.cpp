#include "metering/common/unit_converters.h"
#include "metering/devices/rainforest/messages/price_cluster.h"
#include "metering/types/essential.h"
#include "metering/types/optional.h"

const std::string PriceCluster::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string PriceCluster::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string PriceCluster::FIELDNAME_TIER{ "Tier" };

PriceCluster::PriceCluster(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(IsEssential<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
	m_Tier(IsEssential<Tiers>(node, FIELDNAME_TIER)),
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

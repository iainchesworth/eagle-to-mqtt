#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const PriceCluster& price_cluster)
{
	spdlog::debug("Capturing pricing tier and it's price information set");
	m_PricingTiers.insert_or_assign(price_cluster.Tier(), price_cluster.TierPricing());
}

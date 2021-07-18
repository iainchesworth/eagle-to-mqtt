#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const PriceCluster& price_cluster)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing pricing tier and it's price information set";
	m_PricingTiers.insert_or_assign(price_cluster.Tier(), price_cluster.TierPricing());
}

#ifndef PRICE_CLUSTER_H
#define PRICE_CLUSTER_H

#include <boost/property_tree/ptree.hpp>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/tiers.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/pricing_tier.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class PriceCluster : public IFragmentProcessor
{
public:
	PriceCluster(const boost::property_tree::ptree& node);
	virtual ~PriceCluster();

public:
	Tiers Tier() const;
	PricingTier TierPricing() const;

private:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_Timestamp;
	Tiers m_Tier;
	PricingTier m_TierPricing;
};

#endif // PRICE_CLUSTER_H

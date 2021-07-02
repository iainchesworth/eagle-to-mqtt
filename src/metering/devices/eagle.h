#ifndef EAGLE_H
#define EAGLE_H

#include <boost/property_tree/ptree.hpp>

#include <atomic>
#include <chrono>
#include <ostream>
#include <map>
#include <string>
#include <tuple>

#include "exceptions/not_implemented.h"
#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"
#include "metering/devices/device_connectivity.h"
#include "metering/devices/device_energy_usage.h"
#include "metering/devices/device_stats.h"
#include "metering/fragment_processors/billing_period_list.h"
#include "metering/fragment_processors/block_price_detail.h"
#include "metering/fragment_processors/connection_status.h"
#include "metering/fragment_processors/current_summation.h"
#include "metering/fragment_processors/device_info.h"
#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/fragment_processors/message_cluster.h"
#include "metering/fragment_processors/network_info.h"
#include "metering/fragment_processors/price_cluster.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "metering/fragment_processors/partial_fragment_types/pricing_tier.h"

// Forward declarations
class Eagle_Serializer;

class Eagle : public ISerializable
{
public:
	Eagle();

public:
	virtual void ProcessPayload(const boost::property_tree::ptree& node);

protected:
	virtual void ProcessFragment(const BillingPeriodList& billing_period_list);
	virtual void ProcessFragment(const BlockPriceDetail& block_price_detail);
	virtual void ProcessFragment(const ConnectionStatus& connection_status);
	virtual void ProcessFragment(const CurrentSummation& current_summation);
	virtual void ProcessFragment(const DeviceInfo& device_info);
	virtual void ProcessFragment(const InstantaneousDemand& instantaneous_demand);
	virtual void ProcessFragment(const MessageCluster& network_info);
	virtual void ProcessFragment(const NetworkInfo& network_info);
	virtual void ProcessFragment(const PriceCluster& price_cluster);

protected:
	virtual void ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes);

public:
	DeviceConnectivity Connectivity() const;
	DeviceEnergyUsage EnergyUsage() const;
	DeviceStatistics Statistics() const;

protected:
	DeviceConnectivity m_Connectivity;
	DeviceEnergyUsage m_EnergyUsage;
	DeviceStatistics m_Statistics;

protected:
	EthernetMacId m_EthernetMacId;
	ZigBeeMacId m_ZigbeeMacId;

protected:
	std::string m_FirmwareVersion;
	std::string m_HardwareVersion;
	std::string m_ModelId;

protected:
	PricingTiers m_PricingTiers;

protected:
	std::map<Queues, MeterMessageQueue> m_MeterMessages;

public:
	friend class Eagle_Serializer;
};

#endif // EAGLE_H

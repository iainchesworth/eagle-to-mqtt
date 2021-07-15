#ifndef EAGLE_H
#define EAGLE_H

#include <boost/property_tree/ptree.hpp>

#include <atomic>
#include <chrono>
#include <ostream>
#include <map>
#include <string>
#include <tuple>

#include "interfaces/idevice.h"
#include "interfaces/iserializable.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/common/device_connectivity.h"
#include "metering/devices/rainforest/common/device_energy_usage.h"
#include "metering/devices/rainforest/common/device_stats.h"
#include "metering/devices/rainforest/messages/billing_period_list.h"
#include "metering/devices/rainforest/messages/block_price_detail.h"
#include "metering/devices/rainforest/messages/connection_status.h"
#include "metering/devices/rainforest/messages/current_summation.h"
#include "metering/devices/rainforest/messages/device_info.h"
#include "metering/devices/rainforest/messages/instantaneous_demand.h"
#include "metering/devices/rainforest/messages/message_cluster.h"
#include "metering/devices/rainforest/messages/network_info.h"
#include "metering/devices/rainforest/messages/price_cluster.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/devices/rainforest/messages/partial_message_types/pricing_tier.h"

class Eagle : public IDevice
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
	Rainforest::DeviceConnectivity Connectivity() const;
	Rainforest::DeviceEnergyUsage EnergyUsage() const;
	Rainforest::DeviceStatistics Statistics() const;

protected:
	Rainforest::DeviceConnectivity m_Connectivity;
	Rainforest::DeviceEnergyUsage m_EnergyUsage;
	Rainforest::DeviceStatistics m_Statistics;

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
	virtual boost::json::object Serialize() const;
};

#endif // EAGLE_H

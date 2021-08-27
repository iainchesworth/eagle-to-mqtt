#ifndef EAGLE_H
#define EAGLE_H

#include <boost/json.hpp>
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
	void ProcessPayload(const boost::property_tree::ptree& node) override;

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
	virtual void ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes);

public:
	const Rainforest::DeviceConnectivity& Connectivity() const;
	const Rainforest::DeviceEnergyUsage& EnergyUsage() const;
	const Rainforest::DeviceStatistics& Statistics() const;

private:
	Rainforest::DeviceConnectivity m_Connectivity;
	Rainforest::DeviceEnergyUsage m_EnergyUsage;
	Rainforest::DeviceStatistics m_Statistics;

public:
	const EthernetMacId& Ethernet_MacId() const;
	const ZigBeeMacId& Zigbee_MacId() const;

private:
	EthernetMacId m_EthernetMacId;
	ZigBeeMacId m_ZigbeeMacId;

public:
	const std::string& FirmwareVersion() const;
	const std::string& HardwareVersion() const;
	const std::string& ModelId() const;

private:
	std::string m_FirmwareVersion;
	std::string m_HardwareVersion;
	std::string m_ModelId;

public:
	const PricingTiers& PriceTiers() const;

private:
	PricingTiers m_PricingTiers;

public:
	using MeterMessagesMap = std::map<Queues, MeterMessageQueue>;
	const MeterMessagesMap& MessageQueues() const;

private:
	MeterMessagesMap m_MeterMessages
	{
		// Instantiate the various available meter messages queues.
		std::make_pair(Queues(Queues::QueueTypes::NotSpecified), MeterMessageQueue()),
		std::make_pair(Queues(Queues::QueueTypes::Active), MeterMessageQueue()),
		std::make_pair(Queues(Queues::QueueTypes::CancelPending), MeterMessageQueue()),
		std::make_pair(Queues(Queues::QueueTypes::Unknown), MeterMessageQueue())
	};

public:
	boost::json::object Serialize() const override;
};

#endif // EAGLE_H

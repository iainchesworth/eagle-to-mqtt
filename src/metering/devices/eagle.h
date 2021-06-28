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
#include "metering/devices/device_stats.h"
#include "metering/fragment_processors/connection_status.h"
#include "metering/fragment_processors/current_summation.h"
#include "metering/fragment_processors/device_info.h"
#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/fragment_processors/message_cluster.h"
#include "metering/fragment_processors/network_info.h"
#include "metering/fragment_processors/price_cluster.h"
#include "metering/fragment_processors/partial_fragment_types/demand.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "metering/fragment_processors/partial_fragment_types/pricing_tier.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"

// Forward declarations
class Eagle_Serializer;

class Eagle : public ISerializable
{
public:
	Eagle();

public:
	virtual void ProcessPayload(const boost::property_tree::ptree& node);

protected:
	virtual void ProcessFragment(const ConnectionStatus& connection_status);
	virtual void ProcessFragment(const CurrentSummation& current_summation);
	virtual void ProcessFragment(const DeviceInfo& device_info);
	virtual void ProcessFragment(const InstantaneousDemand& instantaneous_demand);
	virtual void ProcessFragment(const MessageCluster& network_info);
	virtual void ProcessFragment(const NetworkInfo& network_info);
	virtual void ProcessFragment(const PriceCluster& price_cluster);

protected:
	virtual void ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes);

protected:
	DeviceStatistics m_Statistics;

protected:
	EthernetMacId m_EthernetMacId;
	ZigBeeMacId m_ZigbeeMacId;
	ZigBeeMacId m_CoordinatorZigbeeMacId;

protected:
	std::string m_FirmwareVersion;
	std::string m_HardwareVersion;
	std::string m_ModelId;

protected:
	PricingTiers m_PricingTiers;

protected:
	std::map<Queues, MeterMessageQueue> m_MeterMessages;

protected:
	Summation m_TotalDelivered;
	Summation m_TotalReceived;
	std::map<timepoint_from_jan2000, Demand> m_DemandHistory;

public:
	friend class Eagle_Serializer;
};

#endif // EAGLE_H

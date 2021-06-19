#ifndef IEAGLE_H
#define IEAGLE_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <map>

#include "metering/common/demand_in_watts.h"
#include "metering/common/ethernet_mac_id.h"
#include "metering/fragment_processors/connection_status.h"
#include "metering/fragment_processors/current_summation.h"
#include "metering/fragment_processors/device_info.h"
#include "metering/fragment_processors/instantaneous_demand.h"
#include "metering/fragment_processors/network_info.h"

class IEagle
{
public:
	IEagle();

public:
	virtual void ProcessFragment(const ConnectionStatus& connection_status);
	virtual void ProcessFragment(const CurrentSummation& current_summation);
	virtual void ProcessFragment(const DeviceInfo& device_info);
	virtual void ProcessFragment(const InstantaneousDemand& instantaneous_demand);
	virtual void ProcessFragment(const NetworkInfo& network_info);

public:
	virtual void ProcessPayload(const boost::property_tree::ptree& node);

protected:
	EthernetMacId m_DeviceMacId;

private:
	std::map<std::chrono::time_point<std::chrono::system_clock>, DemandInWatts> m_DemandHistory;
};

#endif // IEAGLE_H

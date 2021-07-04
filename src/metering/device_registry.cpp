#include <boost/log/trivial.hpp>

#include "metering/device_registry.h"

DeviceRegistry::DeviceRegistry() :
	m_Registry()
{
	BOOST_LOG_TRIVIAL(debug) << L"Initialising the DeviceRegistry";
}

void DeviceRegistry::Add(const EthernetMacId device_ethernet_mac_id, std::shared_ptr<Eagle> device)
{
	if (!(m_Registry.insert(std::make_pair(device_ethernet_mac_id, device)).second))
	{
		BOOST_LOG_TRIVIAL(warning) << L"Attempted to add multiple devices with the same Ethernet MAC address";
	}
}

std::shared_ptr<Eagle> DeviceRegistry::Find(const EthernetMacId device_ethernet_mac_id)
{
	auto it = m_Registry.find(device_ethernet_mac_id);
	if (m_Registry.end() == it)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Failed to locate a device with a matching Ethernet MAC address";
		return nullptr;
	}
	else
	{
		BOOST_LOG_TRIVIAL(trace) << L"Successfully located a device with a matching Ethernet MAC address";
		return it->second;
	}
}

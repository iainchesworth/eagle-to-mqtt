#include <boost/container_hash/hash.hpp>

#include "metering/common/ethernet_mac_id.h"

EthernetMacId::EthernetMacId() :
	MacId()
{
}

EthernetMacId::EthernetMacId(const std::string& ethernet_mac_id) :
	MacId(ethernet_mac_id)
{
}

bool EthernetMacId::operator==(const EthernetMacId& other) const
{
	return (m_DeviceMacId == other.m_DeviceMacId);
}

std::size_t EthernetMacId::EthernetMacId_Hasher::operator()(const EthernetMacId& key) const
{
	return boost::hash_range(key.m_DeviceMacId.begin(), key.m_DeviceMacId.end());
}

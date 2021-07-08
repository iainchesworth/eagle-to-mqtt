#include <boost/container_hash/hash.hpp>
#include <boost/log/trivial.hpp>

#include "exceptions/missing_message_key.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "metering/type_handlers/optional.h"

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

std::ostream& operator<<(std::ostream& os, const EthernetMacId& ethernet_macid)
{
	os << EthernetMacId::ToString(ethernet_macid);
	return os;
}

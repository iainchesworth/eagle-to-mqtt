#include <boost/container_hash/hash.hpp>
#include <boost/log/trivial.hpp>

#include "exceptions/missing_message_key.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/types/optional.h"

EthernetMacId::EthernetMacId() :
	MacId()
{
}

EthernetMacId::EthernetMacId(const std::string& ethernet_mac_id) :
	MacId(ethernet_mac_id)
{
}

std::size_t EthernetMacId::EthernetMacId_Hasher::operator()(const EthernetMacId& key) const
{
	return boost::hash_range(key.DeviceMacId().cbegin(), key.DeviceMacId().cend());
}

std::ostream& operator<<(std::ostream& os, const EthernetMacId& ethernet_macid)
{
	os << EthernetMacId::ToString(ethernet_macid);
	return os;
}

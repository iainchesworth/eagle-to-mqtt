#include <boost/container_hash/hash.hpp>

#include "exceptions/missing_message_key.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"

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

EthernetMacId EthernetMacId::ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& key)
{
	auto ethernet_id = node.get_optional<EthernetMacId>(key, EthernetMacId::PropertyTreeTranslator());
	if (!ethernet_id.is_initialized())
	{
		throw MissingMessageKey(key);
	}
	else
	{
		// Everything has worked...yay!
	}

	return ethernet_id.get();
}

#ifndef ETHERNET_MAC_ID_H
#define ETHERNET_MAC_ID_H

#include <boost/optional.hpp>
#include <boost/property_tree/ptree.hpp>

#include <sstream>
#include <string>

#include "metering/devices/rainforest/messages/partial_message_types/mac_id.h"

static constexpr uint32_t ETHERNET_MAC_ID_LENGTH_IN_PAIRS{ 6 };

class EthernetMacId : public MacId<ETHERNET_MAC_ID_LENGTH_IN_PAIRS> // Is 6 elements of 2 chars encoded as 0x123456789012.
{
public:
	EthernetMacId();
	explicit EthernetMacId(const std::string& ethernet_mac_id);

public:
	struct EthernetMacId_Hasher
	{
		std::size_t operator()(const EthernetMacId& k) const;
	};

public:
	struct PropertyTreeTranslator
	{
		using external_type = EthernetMacId;
		using internal_type = std::string;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

public:
	friend std::ostream& operator<<(std::ostream& os, const EthernetMacId& ethernet_macid);
};

#endif // ETHERNET_MAC_ID_H

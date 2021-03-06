#ifndef ZIGBEE_MAC_ID_H
#define ZIGBEE_MAC_ID_H

#include <boost/property_tree/ptree.hpp>
#include <boost/optional.hpp>

#include <sstream>
#include <string>

#include "metering/devices/rainforest/messages/partial_message_types/mac_id.h"

static constexpr uint32_t ZIGBEE_MAC_ID_LENGTH_IN_PAIRS{ 8 };

class ZigBeeMacId : public MacId<ZIGBEE_MAC_ID_LENGTH_IN_PAIRS> // Is 8 elements of 2 chars encoded as 0x12345678901234.
{
public:
	ZigBeeMacId();
	explicit ZigBeeMacId(const std::string& zigbee_mac_id);

public:
	struct PropertyTreeTranslator
	{
		using external_type = ZigBeeMacId;
		using internal_type = std::string;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

public:
	friend std::ostream& operator<<(std::ostream& os, const ZigBeeMacId& zigbee_macid);
};

#endif // ZIGBEE_MAC_ID_H

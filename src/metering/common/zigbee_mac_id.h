#ifndef ZIGBEE_MAC_ID_H
#define ZIGBEE_MAC_ID_H

#include <boost/optional/optional.hpp>

#include <string>

#include "metering/common/mac_id.h"

class ZigBeeMacId : public MacId<8> // Is 8 elements of 2 chars encoded as 0x12345678901234.
{
public:
	ZigBeeMacId();
	ZigBeeMacId(const std::string& ethernet_mac_id);
};

struct ZigBeeMacId_PropertyTreeTranslator
{
	typedef ZigBeeMacId external_type;
	typedef std::string internal_type;

	boost::optional<external_type> get_value(const internal_type&)
	{
		return external_type();
	}
};

#endif // ZIGBEE_MAC_ID_H

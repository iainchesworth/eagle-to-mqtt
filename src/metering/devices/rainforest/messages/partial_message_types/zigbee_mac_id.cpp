#include "exceptions/missing_message_key.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"
#include "metering/types/optional.h"

ZigBeeMacId::ZigBeeMacId() :
	MacId()
{
}

ZigBeeMacId::ZigBeeMacId(const std::string& zigbee_mac_id) :
	MacId(zigbee_mac_id)
{
}

std::ostream& operator<<(std::ostream& os, const ZigBeeMacId& zigbee_macid)
{
	os << ZigBeeMacId::ToString(zigbee_macid);
	return os;
}

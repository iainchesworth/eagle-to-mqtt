#include "exceptions/missing_message_key.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"
#include "metering/type_handlers/optional.h"

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

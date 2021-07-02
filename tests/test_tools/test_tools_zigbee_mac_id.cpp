#include "test_tools/test_tools_zigbee_mac_id.h"

std::ostream& operator<<(std::ostream& os, ZigBeeMacId const& zigbee_macid)
{
	os << ZigBeeMacId::ToString(zigbee_macid);
	return os;
}

#include "test_tools/test_tools_ethernet_mac_id.h"

std::ostream& operator<<(std::ostream& os, EthernetMacId const& ethernet_macid)
{
	os << EthernetMacId::ToString(ethernet_macid);
	return os;
}

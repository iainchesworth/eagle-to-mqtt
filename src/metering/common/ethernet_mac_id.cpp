#include "metering/common/ethernet_mac_id.h"

EthernetMacId::EthernetMacId() :
	MacId()
{
}

EthernetMacId::EthernetMacId(const std::string& ethernet_mac_id) :
	MacId(ethernet_mac_id)
{
}

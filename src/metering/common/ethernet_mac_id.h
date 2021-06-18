#ifndef ETHERNET_MAC_ID_H
#define ETHERNET_MAC_ID_H

#include <string>

#include "metering/common/mac_id.h"

class EthernetMacId : public MacId<6> // Is 6 elements of 2 chars encoded as 0x123456789012.
{
public:
	EthernetMacId();
	EthernetMacId(const std::string& ethernet_mac_id);
};

#endif // ETHERNET_MAC_ID_H

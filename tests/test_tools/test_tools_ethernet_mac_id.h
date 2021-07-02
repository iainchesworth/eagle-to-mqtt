#ifndef TEST_TOOLS_ETHERNET_MAC_ID_H
#define TEST_TOOLS_ETHERNET_MAC_ID_H

#include <iomanip>
#include <ostream>

#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"

std::ostream& operator<<(std::ostream& os, EthernetMacId const& ethernet_macid);

#endif // TEST_TOOLS_ETHERNET_MAC_ID_H
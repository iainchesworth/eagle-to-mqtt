#ifndef TEST_TOOLS_ZIGBEE_MAC_ID_H
#define TEST_TOOLS_ZIGBEE_MAC_ID_H

#include <iomanip>
#include <ostream>

#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

std::ostream& operator<<(std::ostream& os, ZigBeeMacId const& zigbee_macid);

#endif // TEST_TOOLS_ZIGBEE_MAC_ID_H
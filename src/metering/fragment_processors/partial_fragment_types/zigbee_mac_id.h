#ifndef ZIGBEE_MAC_ID_H
#define ZIGBEE_MAC_ID_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "metering/fragment_processors/partial_fragment_types/mac_id.h"

static constexpr uint32_t ZIGBEE_MAC_ID_LENGTH_IN_PAIRS{ 8 };

class ZigBeeMacId : public MacId<ZIGBEE_MAC_ID_LENGTH_IN_PAIRS> // Is 8 elements of 2 chars encoded as 0x12345678901234.
{
public:
	ZigBeeMacId();
	ZigBeeMacId(const std::string& zigbee_mac_id);

public:
	static ZigBeeMacId ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& key);
};

#endif // ZIGBEE_MAC_ID_H

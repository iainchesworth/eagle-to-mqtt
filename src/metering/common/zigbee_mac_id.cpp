#include "metering/common/zigbee_mac_id.h"

ZigBeeMacId::ZigBeeMacId() :
	MacId()
{
}

ZigBeeMacId::ZigBeeMacId(const std::string& zigbee_mac_id) :
	MacId(zigbee_mac_id)
{
}

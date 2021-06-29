#include <boost/optional.hpp>

#include "exceptions/missing_message_key.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

ZigBeeMacId::ZigBeeMacId() :
	MacId()
{
}

ZigBeeMacId::ZigBeeMacId(const std::string& zigbee_mac_id) :
	MacId(zigbee_mac_id)
{
}

ZigBeeMacId ZigBeeMacId::ExtractFromPayload(const boost::property_tree::ptree& node, const std::string& key)
{
	auto zigbee_id = node.get_optional<ZigBeeMacId>(key, ZigBeeMacId::PropertyTreeTranslator());
	if (!zigbee_id.is_initialized())
	{
		throw MissingMessageKey(key);
	}
	else
	{
		// Everything has worked...yay!
	}

	return zigbee_id.get();
}

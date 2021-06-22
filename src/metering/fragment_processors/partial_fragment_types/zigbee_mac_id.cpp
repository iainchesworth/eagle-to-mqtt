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
	struct ZigBeeMacId_PropertyTreeTranslator
	{
		typedef ZigBeeMacId external_type;
		typedef std::string internal_type;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

	auto zigbee_id = node.get_optional<ZigBeeMacId>(key, ZigBeeMacId_PropertyTreeTranslator());
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

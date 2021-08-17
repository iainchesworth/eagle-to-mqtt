#include "metering/devices/fronius/messages/partial_message_types/smartload.h"

SmartLoad::SmartLoad()
{
}

SmartLoad SmartLoad::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	return SmartLoad();
}

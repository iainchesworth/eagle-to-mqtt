#include "metering/devices/fronius/messages_types/smartload.h"

SmartLoad::SmartLoad()
{
}

SmartLoad SmartLoad::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	return SmartLoad();
}

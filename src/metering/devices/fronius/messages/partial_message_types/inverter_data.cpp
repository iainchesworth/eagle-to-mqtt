#include "metering/devices/fronius/messages/partial_message_types/inverter_data.h"

InverterData::InverterData()
{
}

InverterData InverterData::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	return InverterData();
}

#include "metering/devices/fronius/messages_types/smart_load_data.h"

SmartLoadData::SmartLoadData(const HardwareBase::HardwareId& id) :
	SymoPayload(id)
{
}

SmartLoadData SmartLoadData::ExtractFromPayload(const boost::property_tree::ptree& node, const HardwareBase::HardwareId& id)
{
	return SmartLoadData(id);
}

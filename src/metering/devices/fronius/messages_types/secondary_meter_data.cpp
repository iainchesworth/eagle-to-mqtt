#include "metering/devices/fronius/messages_types/secondary_meter_data.h"

SecondaryMeterData::SecondaryMeterData(const HardwareBase::HardwareId& id) : 
	SymoPayload(id)
{
}

SecondaryMeterData SecondaryMeterData::ExtractFromPayload(const boost::property_tree::ptree& node, const HardwareBase::HardwareId& id)
{
	return SecondaryMeterData(id);
}

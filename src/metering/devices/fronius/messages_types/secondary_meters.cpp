#include "metering/devices/fronius/messages_types/secondary_meters.h"

SecondaryMeter::SecondaryMeter()
{
}

SecondaryMeter SecondaryMeter::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	return SecondaryMeter();
}

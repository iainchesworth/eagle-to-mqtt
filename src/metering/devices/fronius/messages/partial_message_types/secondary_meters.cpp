#include "metering/devices/fronius/messages/partial_message_types/secondary_meters.h"

SecondaryMeter::SecondaryMeter()
{
}

SecondaryMeter SecondaryMeter::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	return SecondaryMeter();
}

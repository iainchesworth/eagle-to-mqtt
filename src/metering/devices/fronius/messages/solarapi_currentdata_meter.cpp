#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages/solarapi_currentdata_meter.h"

SolarApi_CurrentData_Meter::SolarApi_CurrentData_Meter(const boost::property_tree::ptree& node) :
	SolarApi_Base_Message(node)
{
	spdlog::debug("Processing SolarApi_CurrentData_Meter() - meter data");
}

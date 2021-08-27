#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages/solarapi_currentdata_stringcontrol.h"

SolarApi_CurrentData_StringControl::SolarApi_CurrentData_StringControl(const boost::property_tree::ptree& node) :
	SolarApi_Base_Message(node)
{
	spdlog::debug("Processing SolarApi_CurrentData_StringControl() - string control data");
}

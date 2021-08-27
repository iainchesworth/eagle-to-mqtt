#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages/solarapi_logdata_errorsandevents.h"

SolarApi_LogData_ErrorsAndEvents::SolarApi_LogData_ErrorsAndEvents(const boost::property_tree::ptree& node) :
	SolarApi_Base_Message(node)
{
	spdlog::debug("Processing SolarApi_LogData_ErrorsAndEvents() - error and event data");
}

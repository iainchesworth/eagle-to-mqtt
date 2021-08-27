#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages/solarapi_currentdata_sensorcard.h"

SolarApi_CurrentData_SensorCard::SolarApi_CurrentData_SensorCard(const boost::property_tree::ptree& node) :
	SolarApi_Base_Message(node)
{
	spdlog::debug("Processing SolarApi_CurrentData_SensorCard() - sensor data");
}

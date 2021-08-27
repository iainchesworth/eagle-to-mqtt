#ifndef SOLARAPI_CURRENTDATA_SENSORCARD_H
#define SOLARAPI_CURRENTDATA_SENSORCARD_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/messages/solarapi_base_message.h"

class SolarApi_CurrentData_SensorCard : public SolarApi_Base_Message
{
public:
	explicit SolarApi_CurrentData_SensorCard(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_SensorCard() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_SENSORCARD_H

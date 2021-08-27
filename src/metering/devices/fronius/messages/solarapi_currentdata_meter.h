#ifndef SOLARAPI_CURRENTDATA_METER_H
#define SOLARAPI_CURRENTDATA_METER_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/messages/solarapi_base_message.h"

class SolarApi_CurrentData_Meter : public SolarApi_Base_Message
{
public:
	explicit SolarApi_CurrentData_Meter(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_Meter() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_STRINGCONTROL_H

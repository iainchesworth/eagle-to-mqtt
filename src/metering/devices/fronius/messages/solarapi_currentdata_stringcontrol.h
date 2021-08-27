#ifndef SOLARAPI_CURRENTDATA_STRINGCONTROL_H
#define SOLARAPI_CURRENTDATA_STRINGCONTROL_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/messages/solarapi_base_message.h"

class SolarApi_CurrentData_StringControl : public SolarApi_Base_Message
{
public:
	explicit SolarApi_CurrentData_StringControl(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_StringControl() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_STRINGCONTROL_H

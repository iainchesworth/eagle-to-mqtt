#ifndef SOLARAPI_CURRENTDATA_STRINGCONTROL_H
#define SOLARAPI_CURRENTDATA_STRINGCONTROL_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_CurrentData_StringControl
{
public:
	explicit SolarApi_CurrentData_StringControl(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_StringControl() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_STRINGCONTROL_H

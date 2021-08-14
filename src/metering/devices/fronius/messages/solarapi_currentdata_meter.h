#ifndef SOLARAPI_CURRENTDATA_METER_H
#define SOLARAPI_CURRENTDATA_METER_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_CurrentData_Meter
{
public:
	explicit SolarApi_CurrentData_Meter(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_Meter() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_STRINGCONTROL_H

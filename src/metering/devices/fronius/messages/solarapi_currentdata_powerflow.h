#ifndef SOLARAPI_CURRENTDATA_POWERFLOW_H
#define SOLARAPI_CURRENTDATA_POWERFLOW_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_CurrentData_PowerFlow
{
public:
	explicit SolarApi_CurrentData_PowerFlow(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_PowerFlow() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_POWERFLOW_H

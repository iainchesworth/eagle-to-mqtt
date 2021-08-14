#ifndef SOLARAPI_LOGDATA_DATA_H
#define SOLARAPI_LOGDATA_DATA_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_LogData_Data
{
public:
	explicit SolarApi_LogData_Data(const boost::property_tree::ptree& node);
	virtual ~SolarApi_LogData_Data() = default;

public:

};

#endif // SOLARAPI_LOGDATA_DATA_H

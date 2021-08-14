#ifndef SOLARAPI_CURRENTDATA_SENSORCARD_H
#define SOLARAPI_CURRENTDATA_SENSORCARD_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_CurrentData_SensorCard
{
public:
	explicit SolarApi_CurrentData_SensorCard(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_SensorCard() = default;

public:

};

#endif // SOLARAPI_CURRENTDATA_SENSORCARD_H

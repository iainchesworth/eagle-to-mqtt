#ifndef SOLARAPI_LOGDATA_ERRORSANDEVENTS_H
#define SOLARAPI_LOGDATA_ERRORSANDEVENTS_H

#include <boost/property_tree/ptree.hpp>

class SolarApi_LogData_ErrorsAndEvents
{
public:
	explicit SolarApi_LogData_ErrorsAndEvents(const boost::property_tree::ptree& node);
	virtual ~SolarApi_LogData_ErrorsAndEvents() = default;

public:

};

#endif // SOLARAPI_LOGDATA_ERRORSANDEVENTS_H

#ifndef SOLARAPI_BASE_MESSAGE_H
#define SOLARAPI_BASE_MESSAGE_H

#include <boost/property_tree/ptree.hpp>

#include "metering/common/timestamps.h"

class SolarApi_Base_Message
{
public:
	explicit SolarApi_Base_Message(const boost::property_tree::ptree& node);

public:
	const UnixTimepoint& Timestamp() const;

private:
	UnixTimepoint m_Timestamp;
};

#endif // SOLARAPI_BASE_MESSAGE_H

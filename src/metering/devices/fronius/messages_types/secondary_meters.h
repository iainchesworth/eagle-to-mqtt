#ifndef SECONDARY_METER_H
#define SECONDARY_METER_H

#include <boost/property_tree/ptree.hpp>

class SecondaryMeter
{
public:
	SecondaryMeter();

public:
	static SecondaryMeter ExtractFromPayload(const boost::property_tree::ptree& node);
};


#endif // SECONDARY_METER_H

#ifndef SMARTLOAD_H
#define SMARTLOAD_H

#include <boost/property_tree/ptree.hpp>

class SmartLoad
{
public:
	SmartLoad();

public:
	static SmartLoad ExtractFromPayload(const boost::property_tree::ptree& node);
};

#endif // SMARTLOAD_H

#ifndef IDEVICE_API_H
#define IDEVICE_API_H

#include <boost/property_tree/ptree.hpp>

#include <memory>

#include "interfaces/iserializable.h"

class IDevice : public ISerializable
{
public:
	explicit IDevice();

public:
	virtual void ProcessPayload(const boost::property_tree::ptree& node) = 0;
};

#endif // IDEVICE_API_H

#ifndef SYMO_H
#define SYMO_H

#include <boost/property_tree/ptree.hpp>

#include <memory>

#include "interfaces/idevice.h"
#include "interfaces/iserializer.h"
#include "interfaces/iserializable.h"
#include "metering/devices/fronius/common/device_stats.h"

class Symo : public IDevice
{
public:
	Symo();

public:
	virtual void ProcessPayload(const boost::property_tree::ptree& node);

protected:
	virtual void ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes);

public:
	Fronius::DeviceStatistics Statistics() const;

protected:
	Fronius::DeviceStatistics m_Statistics;

public:
	friend class Symo_Serializer;
	virtual boost::json::object Serialize() const;
};

#endif // SYMO_H

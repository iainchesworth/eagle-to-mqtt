#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <boost/property_tree/ptree.hpp>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/protocol_types.h"
#include "metering/common/zigbee_mac_id.h"

class NetworkInfo : public IFragmentProcessor
{
public:
	NetworkInfo(const boost::property_tree::ptree& node);

private:
	ZigBeeMacId m_DeviceMacId;
	ZigBeeMacId m_CoordMacId;
	StatusTypes m_Status;
	std::string m_Description;
	std::string m_StatusCode;
	ZigBeeMacId m_ExtPanId;
	std::string m_Channel;
	std::string m_ShortAddr;
	std::string m_LinkStrength;
};

#endif // NETWORK_INFO_H

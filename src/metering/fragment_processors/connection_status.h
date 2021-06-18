#ifndef CONNECTION_STATUS_H
#define CONNECTION_STATUS_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/protocol_types.h"
#include "metering/common/zigbee_mac_id.h"

class ConnectionStatus : public IFragmentProcessor
{
public:
	ConnectionStatus(const boost::property_tree::ptree& node);

private:
	ZigBeeMacId m_DeviceMacId;
	ZigBeeMacId m_MeterMacId;
	StatusTypes m_Status;
	ZigBeeMacId m_ExtPanId;
	std::string m_Channel;
	std::string m_ShortAddr;
	std::string m_LinkStrength;
	ProtocolTypes m_Protocol;
};

#endif // CONNECTION_STATUS_H

#ifndef CONNECTION_STATUS_H
#define CONNECTION_STATUS_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/protocol_types.h"
#include "metering/common/statuses.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class ConnectionStatus : public IFragmentProcessor
{
public:
	ConnectionStatus(const boost::property_tree::ptree& node);
	virtual ~ConnectionStatus();

public:
	ZigBeeMacId Meter_MacId() const;
	ZigBeeMacId External_PanId() const;
	std::string ShortAddr() const;

public:
	Statuses Status() const;

public:
	std::string Channel() const;
	uint8_t LinkStrength() const;

private:
	ZigBeeMacId m_MeterMacId;
	Statuses m_Status;
	ZigBeeMacId m_ExtPanId;
	std::string m_Channel;
	std::string m_ShortAddr;
	uint8_t m_LinkStrength;
};

#endif // CONNECTION_STATUS_H

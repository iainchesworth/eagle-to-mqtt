#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/statuses.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class NetworkInfo : public IFragmentProcessor
{
public:
	NetworkInfo(const boost::property_tree::ptree& node);
	virtual ~NetworkInfo();

public:
	ZigBeeMacId CoordinatorZigbeeId() const;

public:
	Statuses Status() const;
	uint8_t StatusCode() const;

public:
	std::string Channel() const;
	uint8_t LinkStrength() const;

private:
	ZigBeeMacId m_CoordMacId;
	Statuses m_Status;
	std::string m_Description;
	uint8_t m_StatusCode;
	ZigBeeMacId m_ExtPanId;
	std::string m_Channel;
	std::string m_ShortAddr;
	uint8_t m_LinkStrength;
};

#endif // NETWORK_INFO_H

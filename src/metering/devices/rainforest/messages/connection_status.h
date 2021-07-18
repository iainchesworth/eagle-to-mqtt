#ifndef CONNECTION_STATUS_H
#define CONNECTION_STATUS_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/statuses.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class ConnectionStatus : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_STATUS;
	static const std::string FIELDNAME_EXTPANID;
	static const std::string FIELDNAME_CHANNEL;
	static const std::string FIELDNAME_SHORTADDR;
	static const std::string FIELDNAME_LINKSTRENGTH;

public:
	ConnectionStatus(const boost::property_tree::ptree& node);
	virtual ~ConnectionStatus();

public:
	std::optional<ZigBeeMacId> Meter_MacId() const;
	std::optional<ZigBeeMacId> Extended_PanId() const;
	std::optional<std::string> ShortAddr() const;

public:
	std::optional<Statuses> Status() const;

public:
	std::optional<std::string> Channel() const;
	std::optional<uint8_t> LinkStrength() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	std::optional<Statuses> m_Status;
	std::optional<ZigBeeMacId> m_ExtPanId;
	std::optional<std::string> m_Channel;
	std::optional<std::string> m_ShortAddr;
	std::optional<uint8_t> m_LinkStrength;
};

#endif // CONNECTION_STATUS_H

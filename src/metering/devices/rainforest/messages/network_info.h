#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/statuses.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class NetworkInfo : public IFragmentProcessor
{
	static const std::string FIELDNAME_COORDMACID;
	static const std::string FIELDNAME_STATUS;
	static const std::string FIELDNAME_DESCRIPTION;
	static const std::string FIELDNAME_STATUSCODE;
	static const std::string FIELDNAME_EXTPANID;
	static const std::string FIELDNAME_CHANNEL;
	static const std::string FIELDNAME_SHORTADDR;
	static const std::string FIELDNAME_LINKSTRENGTH;

public:
	NetworkInfo(const boost::property_tree::ptree& node);
	virtual ~NetworkInfo();

public:
	std::optional<ZigBeeMacId> CoordinatorZigbeeId() const;

public:
	std::optional<Statuses> Status() const;
	std::optional<uint8_t> StatusCode() const;

public:
	std::optional<std::string> Channel() const;
	std::optional<uint8_t> LinkStrength() const;

private:
	std::optional<ZigBeeMacId> m_CoordMacId;
	std::optional<Statuses> m_Status;
	std::optional<std::string> m_Description;
	std::optional<uint8_t> m_StatusCode;
	std::optional<ZigBeeMacId> m_ExtPanId;
	std::optional<std::string> m_Channel;
	std::optional<std::string> m_ShortAddr;
	std::optional<uint8_t> m_LinkStrength;
};

#endif // NETWORK_INFO_H

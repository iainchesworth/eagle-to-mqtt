#include "metering/devices/rainforest/messages/network_info.h"

#include "metering/types/essential.h"
#include "metering/types/integer.h"
#include "metering/types/optional.h"

const std::string NetworkInfo::FIELDNAME_COORDMACID{ "CoordMacId" };
const std::string NetworkInfo::FIELDNAME_STATUS{ "Status" };
const std::string NetworkInfo::FIELDNAME_DESCRIPTION{ "Description" };
const std::string NetworkInfo::FIELDNAME_STATUSCODE{ "StatusCode" };
const std::string NetworkInfo::FIELDNAME_EXTPANID{ "ExtPanId" };
const std::string NetworkInfo::FIELDNAME_CHANNEL{ "Channel" };
const std::string NetworkInfo::FIELDNAME_SHORTADDR{ "ShortAddr" };
const std::string NetworkInfo::FIELDNAME_LINKSTRENGTH{ "LinkStrength" };

NetworkInfo::NetworkInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_CoordMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_COORDMACID)),
	m_Status(IsOptional<Statuses>(node, FIELDNAME_STATUS)),
	m_Description(IsOptional<std::string>(node, FIELDNAME_DESCRIPTION)),
	m_StatusCode(IsOptional<uint8_t>(node, FIELDNAME_STATUSCODE)),
	m_ExtPanId(IsOptional<ZigBeeMacId>(node, FIELDNAME_EXTPANID)),
	m_Channel(IsOptional<std::string>(node, FIELDNAME_CHANNEL)),
	m_ShortAddr(IsOptional<std::string>(node, FIELDNAME_SHORTADDR)),
	m_LinkStrength(IsOptional<uint8_t>(node, FIELDNAME_LINKSTRENGTH))
{
}

std::optional<ZigBeeMacId> NetworkInfo::CoordinatorZigbeeId() const
{
	return m_CoordMacId;
}

std::optional<Statuses> NetworkInfo::Status() const
{
	return m_Status;
}

std::optional<uint8_t> NetworkInfo::StatusCode() const
{
	return m_StatusCode;
}

std::optional<std::string> NetworkInfo::Channel() const
{
	return m_Channel;
}

std::optional<uint8_t> NetworkInfo::LinkStrength() const
{
	return m_LinkStrength;
}

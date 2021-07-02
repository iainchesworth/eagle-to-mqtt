#include "metering/fragment_processors/connection_status.h"
#include "metering/type_handlers/optional.h"

const std::string ConnectionStatus::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string ConnectionStatus::FIELDNAME_STATUS{ "Status" };
const std::string ConnectionStatus::FIELDNAME_EXTPANID{"ExtPanId"};
const std::string ConnectionStatus::FIELDNAME_CHANNEL{ "Channel" };
const std::string ConnectionStatus::FIELDNAME_SHORTADDR{ "ShortAddr" };
const std::string ConnectionStatus::FIELDNAME_LINKSTRENGTH{ "LinkStrength" };

ConnectionStatus::ConnectionStatus(const boost::property_tree::ptree& node) : 
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Status(IsOptional<Statuses>(node, FIELDNAME_STATUS)),
	m_ExtPanId(IsOptional<ZigBeeMacId>(node, FIELDNAME_EXTPANID)),
	m_Channel(IsOptional<std::string>(node, FIELDNAME_CHANNEL)),
	m_ShortAddr(IsOptional<std::string>(node, FIELDNAME_SHORTADDR)),
	m_LinkStrength(IsOptional<uint8_t>(node, FIELDNAME_LINKSTRENGTH))
{
}

ConnectionStatus::~ConnectionStatus()
{
}

std::optional<ZigBeeMacId> ConnectionStatus::Meter_MacId() const
{
	return m_MeterMacId;
}

std::optional<ZigBeeMacId> ConnectionStatus::Extended_PanId() const
{
	return m_ExtPanId;
}

std::optional<std::string> ConnectionStatus::ShortAddr() const
{
	return m_ShortAddr;
}

std::optional<Statuses> ConnectionStatus::Status() const
{
	return m_Status;
}

std::optional<std::string> ConnectionStatus::Channel() const
{
	return m_Channel;
}

std::optional<uint8_t> ConnectionStatus::LinkStrength() const
{
	return m_LinkStrength;
}

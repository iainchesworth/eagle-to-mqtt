#include "metering/fragment_processors/network_info.h"

#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/expected.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

NetworkInfo::NetworkInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_CoordMacId(IsExpected<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "CoordMacId"); })),
	m_Status(IFragmentProcessor::ProcessStatus(node)),
	m_Description(IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("Description"); })),
	m_StatusCode(IsOptional<uint8_t>([&node]() -> uint8_t { return GetValue_UInt8(node, "StatusCode"); })),
	m_ExtPanId(IsOptional<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "ExtPanId"); })),
	m_Channel(IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("Channel"); })),
	m_ShortAddr(IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("ShortAddr"); })),
	m_LinkStrength(IsExpected<uint8_t>([&node]() -> uint8_t { return GetValue_UInt8(node, "LinkStrength"); }))
{
}

NetworkInfo::~NetworkInfo()
{
}

ZigBeeMacId NetworkInfo::CoordinatorZigbeeId() const
{
	return m_CoordMacId;
}

Statuses NetworkInfo::Status() const
{
	return m_Status;
}

uint8_t NetworkInfo::StatusCode() const
{
	return m_StatusCode;
}

std::string NetworkInfo::Channel() const
{
	return m_Channel;
}

uint8_t NetworkInfo::LinkStrength() const
{
	return m_LinkStrength;
}

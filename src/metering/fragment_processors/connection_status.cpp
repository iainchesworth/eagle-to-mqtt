#include "metering/fragment_processors/connection_status.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

ConnectionStatus::ConnectionStatus(const boost::property_tree::ptree& node) : 
	IFragmentProcessor(node),
	m_MeterMacId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Status(IFragmentProcessor::ProcessStatus(node)),
	m_ExtPanId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "ExtPanId"); })),
	m_Channel(IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("Channel"); })),
	m_ShortAddr(IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("ShortAddr"); })),
	m_LinkStrength(IsEssential<uint8_t>([&node]() -> uint8_t { return GetValue_UInt8(node, "LinkStrength"); }))
{
}

ConnectionStatus::~ConnectionStatus()
{
}

ZigBeeMacId ConnectionStatus::Meter_MacId() const
{
	return m_MeterMacId;
}

ZigBeeMacId ConnectionStatus::External_PanId() const
{
	return m_ExtPanId;
}

std::string ConnectionStatus::ShortAddr() const
{
	return m_ShortAddr;
}

Statuses ConnectionStatus::Status() const
{
	return m_Status;
}

std::string ConnectionStatus::Channel() const
{
	return m_Channel;
}

uint8_t ConnectionStatus::LinkStrength() const
{
	return m_LinkStrength;
}

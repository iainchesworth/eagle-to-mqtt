#include "metering/fragment_processors/connection_status.h"

ConnectionStatus::ConnectionStatus(const boost::property_tree::ptree& node) : 
	IFragmentProcessor(),
	m_DeviceMacId(node.get<std::string>("DeviceMacId")),
	m_MeterMacId(node.get<std::string>("MeterMacId")),
	m_Status(IFragmentProcessor::ProcessOptionalStatus(node)),
	m_ExtPanId(IFragmentProcessor::ProcessOptionalTag<ZigBeeMacId>(node, "ExtPanId", ZigBeeMacId())),
	m_Channel(node.get<std::string>("Channel")),
	m_ShortAddr(node.get<std::string>("ShortAddr")),
	m_LinkStrength(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "LinkStrength", "")),
	m_Protocol{ IFragmentProcessor::ProcessOptionalProtocol(node) }
{
}

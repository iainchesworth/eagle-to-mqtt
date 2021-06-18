#include "metering/fragment_processors/network_info.h"

NetworkInfo::NetworkInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(),
	m_DeviceMacId(node.get<std::string>("DeviceMacId")),
	m_CoordMacId(IFragmentProcessor::ProcessOptionalTag<ZigBeeMacId>(node, "CoordMacId", ZigBeeMacId())),
	m_Status(IFragmentProcessor::ProcessOptionalStatus(node)),
	m_Description(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "Description", "")),
	m_StatusCode(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "StatusCode", "")),
	m_ExtPanId(IFragmentProcessor::ProcessOptionalTag<ZigBeeMacId>(node, "ExtPanId", ZigBeeMacId())),
	m_Channel(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "Channel", "")),
	m_ShortAddr(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "ShortAddr", "")),
	m_LinkStrength(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "LinkStrength", ""))
{
}

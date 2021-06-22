#include "interfaces/ifragmentprocessor.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/optional.h"

IFragmentProcessor::IFragmentProcessor(const boost::property_tree::ptree& node):
	m_DeviceMacId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "DeviceMacId"); })),
	m_Protocol{ IFragmentProcessor::ProcessProtocol(node) }
{
}

ZigBeeMacId IFragmentProcessor::DeviceMacId() const
{
	return m_DeviceMacId;
}

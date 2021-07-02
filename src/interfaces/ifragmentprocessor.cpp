#include "interfaces/ifragmentprocessor.h"
#include "metering/type_handlers/optional.h"

IFragmentProcessor::IFragmentProcessor(const boost::property_tree::ptree& node):
	m_DeviceMacId(IsOptional<ZigBeeMacId>(node, "DeviceMacId")),
	m_Protocol(IsOptional<Protocols>(node, "Protocol"))
{
}

std::optional<ZigBeeMacId> IFragmentProcessor::DeviceMacId() const
{
	return m_DeviceMacId;
}

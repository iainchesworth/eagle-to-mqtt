#include <string>

#include "metering/fragment_processors/message_cluster.h"
#include "metering/type_handlers/essential.h"

MessageCluster::MessageCluster(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsEssential<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
	m_MeterMessage(MeterMessage::ExtractFromPayload(node)),
	m_Queue(IsEssential<Queues>([&node]() -> Queues { return Queues::FromString(node.get<std::string>("Queue")); }))
{
}

MessageCluster::~MessageCluster()
{
}

timepoint_from_jan2000 MessageCluster::Timestamp() const
{
	return m_Timestamp;
}

MeterMessage MessageCluster::Message() const
{
	return m_MeterMessage;
}

Queues MessageCluster::Queue() const
{
	return m_Queue;
}

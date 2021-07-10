#include <string>

#include "metering/fragment_processors/message_cluster.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/optional.h"

const std::string MessageCluster::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string MessageCluster::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string MessageCluster::FIELDNAME_QUEUE{ "Queue" };

MessageCluster::MessageCluster(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(IsEssential<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
	m_MeterMessage(MeterMessage::ExtractFromPayload(node)),
	m_Queue(IsEssential<Queues>(node, FIELDNAME_QUEUE))
{
}

MessageCluster::~MessageCluster()
{
}

ZigbeeTimepoint MessageCluster::Timestamp() const
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

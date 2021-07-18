#ifndef MESSAGE_CLUSTER_H
#define MESSAGE_CLUSTER_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/queues.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/meter_message.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class MessageCluster : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;
	static const std::string FIELDNAME_QUEUE;

public:
	MessageCluster(const boost::property_tree::ptree& node);
	virtual ~MessageCluster();

public:
	ZigbeeTimepoint Timestamp() const;
	MeterMessage Message() const;
	Queues Queue() const;

public:
	std::optional<ZigBeeMacId> m_MeterMacId;
	ZigbeeTimepoint m_Timestamp;
	MeterMessage m_MeterMessage;
	Queues m_Queue;
};

#endif // MESSAGE_CLUSTER_H

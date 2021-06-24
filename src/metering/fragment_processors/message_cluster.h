#ifndef MESSAGE_CLUSTER_H
#define MESSAGE_CLUSTER_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/queues.h"
#include "metering/fragment_processors/partial_fragment_types/meter_message.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class MessageCluster : public IFragmentProcessor
{
public:
	MessageCluster(const boost::property_tree::ptree& node);
	virtual ~MessageCluster();

public:
	timepoint_from_jan2000 Timestamp() const;
	MeterMessage Message() const;
	Queues Queue() const;

public:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_Timestamp;
	MeterMessage m_MeterMessage;
	Queues m_Queue;
};

#endif // MESSAGE_CLUSTER_H

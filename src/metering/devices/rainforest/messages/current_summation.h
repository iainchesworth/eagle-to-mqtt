#ifndef CURRENT_SUMMATION_H
#define CURRENT_SUMMATION_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/energy_value.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class CurrentSummation : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;
	static const std::string FIELDNAME_SUMMATIONDELIVERED;
	static const std::string FIELDNAME_SUMMATIONRECEIVED;

public:
	explicit CurrentSummation(const boost::property_tree::ptree& node);
	virtual ~CurrentSummation() = default;

public:
	std::optional<Usage> Delivered() const;
	std::optional<Usage> Received() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	std::optional<ZigbeeTimepoint> m_TimeStamp;
	std::optional<Usage> m_SummationDelivered;
	std::optional<Usage> m_SummationReceived;
};

#endif // CURRENT_SUMMATION_H

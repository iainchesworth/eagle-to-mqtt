#ifndef CURRENT_SUMMATION_H
#define CURRENT_SUMMATION_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/summation.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class CurrentSummation : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;
	static const std::string FIELDNAME_SUMMATIONDELIVERED;
	static const std::string FIELDNAME_SUMMATIONRECEIVED;

public:
	CurrentSummation(const boost::property_tree::ptree& node);
	virtual ~CurrentSummation();

public:
	std::optional<Summation> Delivered() const;
	std::optional<Summation> Received() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	std::optional<ZigbeeTimepoint> m_TimeStamp;
	std::optional<Summation> m_SummationDelivered;
	std::optional<Summation> m_SummationReceived;
};

#endif // CURRENT_SUMMATION_H

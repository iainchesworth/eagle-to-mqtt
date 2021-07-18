#ifndef BILLING_PERIOD_LIST_H
#define BILLING_PERIOD_LIST_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <optional>
#include <cstdint>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class BillingPeriodList : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;
	static const std::string FIELDNAME_NUMBEROFPERIODS;
	static const std::string FIELDNAME_CURRENTSTART;
	static const std::string FIELDNAME_CURRENTDURATION;

public:
	BillingPeriodList(const boost::property_tree::ptree& node);
	virtual ~BillingPeriodList();

public:
	std::chrono::time_point<std::chrono::system_clock> CurrentPeriodStart() const;
	std::chrono::time_point<std::chrono::system_clock> CurrentPeriodEnd() const;
	uint8_t NumberOfPeriods() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	std::optional<ZigbeeTimepoint> m_Timestamp;
	uint8_t m_NumberOfPeriods;
	std::chrono::time_point<std::chrono::system_clock> m_Start;
	std::chrono::minutes m_Duration;
};

#endif // BILLING_PERIOD_LIST_H

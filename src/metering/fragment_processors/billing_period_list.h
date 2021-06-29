#ifndef BILLING_PERIOD_LIST_H
#define BILLING_PERIOD_LIST_H

#include <boost/property_tree/ptree.hpp>

#include <chrono>
#include <cstdint>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/timestamps.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class BillingPeriodList : public IFragmentProcessor
{
public:
	BillingPeriodList(const boost::property_tree::ptree& node);
	virtual ~BillingPeriodList();

public:
	std::chrono::time_point<std::chrono::system_clock> CurrentPeriodStart() const;
	std::chrono::time_point<std::chrono::system_clock> CurrentPeriodEnd() const;
	uint8_t NumberOfPeriods() const;

private:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_Timestamp;
	uint8_t m_NumberOfPeriods;
	std::chrono::time_point<std::chrono::system_clock> m_Start;
	std::chrono::minutes m_Duration;
};

#endif // BILLING_PERIOD_LIST_H

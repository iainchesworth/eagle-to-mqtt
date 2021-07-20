#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const BillingPeriodList& billing_period_list)
{
	BOOST_LOG_TRIVIAL(trace) << L"ProcessFragment(BillingPeriodList) - not handled";
}

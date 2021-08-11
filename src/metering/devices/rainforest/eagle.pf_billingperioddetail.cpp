#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const BillingPeriodList& billing_period_list)
{
	spdlog::trace("ProcessFragment(BillingPeriodList) - not handled");
}

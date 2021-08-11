#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle-200/eagle_200.h"

Eagle200::Eagle200() : 
	Eagle()
{
}

void Eagle200::ProcessFragment(const NetworkInfo& network_info)
{
	spdlog::debug("Eagle Bug: Received unexpected NetworkInfo fragment (see Uploader API migration document, section 2.2).");
	Eagle::ProcessFragment(network_info);
}

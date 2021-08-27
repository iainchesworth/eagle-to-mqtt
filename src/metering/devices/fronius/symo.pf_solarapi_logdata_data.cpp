#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_LogData_Data& solarapi_logdata_data)
{
	spdlog::trace("ProcessFragment(SolarApi_LogData_Data) - not handled");
}

#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_LogData_ErrorsAndEvents& solarapi_logdata_errorsandevents)
{
	spdlog::trace("ProcessFragment(SolarApi_LogData_ErrorsAndEvents) - not handled");
}

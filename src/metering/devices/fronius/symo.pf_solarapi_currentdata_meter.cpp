#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_Meter& solarapi_currentdata_meter)
{
	spdlog::trace("ProcessFragment(SolarApi_CurrentData_Meter) - not handled");
}

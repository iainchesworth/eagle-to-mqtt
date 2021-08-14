#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::trace("ProcessFragment(SolarApi_CurrentData_PowerFlow) - not handled");
}

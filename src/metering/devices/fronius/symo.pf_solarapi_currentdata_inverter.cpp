#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_Inverter& solarapi_currentdata_inverter)
{
	spdlog::trace("ProcessFragment(SolarApi_CurrentData_Inverter) - not handled");
}

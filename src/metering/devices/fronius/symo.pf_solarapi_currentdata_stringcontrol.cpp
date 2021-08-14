#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_StringControl& solarapi_currentdata_stringcontrol)
{
	spdlog::trace("ProcessFragment(SolarApi_CurrentData_StringControl) - not handled");
}

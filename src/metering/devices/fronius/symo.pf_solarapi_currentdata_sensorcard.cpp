#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_SensorCard& solarapi_currentdata_sensorcard)
{
	spdlog::trace("ProcessFragment(SolarApi_CurrentData_SensorCard) - not handled");
}

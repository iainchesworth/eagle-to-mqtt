#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_solarapi_inverter.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_Inverter& solarapi_currentdata_inverter)
{
	spdlog::debug("Capturing SolarAPI Inverter information");

	auto solarapi_inverter_notif = std::make_shared<Notification_SolarApi_Inverter>(0);

	NotificationManagerSingleton()->Dispatch(solarapi_inverter_notif);
}

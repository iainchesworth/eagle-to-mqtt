#include <spdlog/spdlog.h>

#include "metering/devices/fronius/symo.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_solarapi_powerflow.h"

void Symo::ProcessFragment(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow)
{
	spdlog::debug("Capturing SolarAPI PowerFlow information");

	auto solarapi_powerflow_notif = std::make_shared<Notification_SolarApi_PowerFlow>(0);

	NotificationManagerSingleton()->Dispatch(solarapi_powerflow_notif);
}

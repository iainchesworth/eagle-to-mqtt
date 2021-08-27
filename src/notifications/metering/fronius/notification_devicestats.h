#ifndef NOTIFICATION_FRONIUS_DEVICESTATS_H
#define NOTIFICATION_FRONIUS_DEVICESTATS_H

#include <boost/signals2/signal.hpp>

#include <cstdint>
#include <string>

#include "metering/common/timestamps.h"
#include "metering/devices/fronius/common/device_stats.h"
#include "notifications/common/notification_payload_types.h"
#include "notifications/metering/notification_base_devicestats.h"
#include "notifications/metering/notification_publishpayload.h"

namespace Fronius
{

class Notification_DeviceStats : public Notification_BaseDeviceStats<SymoNotification_PublishPayload>
{
	static const std::string MAPKEY_CURRENTDATA_INVERTERCOUNT;
	static const std::string MAPKEY_CURRENTDATA_SENSORCARDCOUNT;
	static const std::string MAPKEY_CURRENTDATA_STRINGCONTROLCOUNT;
	static const std::string MAPKEY_CURRENTDATA_METERCOUNT;
	static const std::string MAPKEY_CURRENTDATA_POWERFLOWCOUNT;
	static const std::string MAPKEY_LOGDATA_DATACOUNT;
	static const std::string MAPKEY_LOGDATA_ERRORSANDEVENTSCOUNT;

public:
	explicit Notification_DeviceStats(SymoNotification_PublishPayload::Types::DeviceId device_id);

public:
	Notification_DeviceStats& DeviceStats(const Fronius::DeviceStatistics& statistics);

public:
	Notification_DeviceStats& SolarAPI_CurrentData_InverterCount(const uint64_t& currentdata_invertercount);
	Notification_DeviceStats& SolarAPI_CurrentData_SensorCardCount(const uint64_t& currentdata_sensorcardcount);
	Notification_DeviceStats& SolarAPI_CurrentData_StringControlCount(const uint64_t& currentdata_stringcontrolcount);
	Notification_DeviceStats& SolarAPI_CurrentData_MeterCount(const uint64_t& currentdata_metercount);
	Notification_DeviceStats& SolarAPI_CurrentData_PowerFlowCount(const uint64_t& currentdata_powerflowcount);
	Notification_DeviceStats& SolarAPI_LogData_DataCount(const uint64_t& logdata_datacount);
	Notification_DeviceStats& SolarAPI_LogData_ErrorsAndEventsCount(const uint64_t& logdata_errorsandeventscount);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

}
// namespace Fronius

#endif // NOTIFICATION_FRONIUS_DEVICESTATS_H

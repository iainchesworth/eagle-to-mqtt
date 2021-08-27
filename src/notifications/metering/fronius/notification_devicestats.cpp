#include "metering/common/timestamps.h"
#include "notifications/metering/fronius/notification_devicestats.h"

using namespace Fronius;

const std::string Notification_DeviceStats::MAPKEY_CURRENTDATA_INVERTERCOUNT{ "solarapi_currentdata_invertercount" };
const std::string Notification_DeviceStats::MAPKEY_CURRENTDATA_SENSORCARDCOUNT{ "solarapi_currentdata_sensorcardcount" };
const std::string Notification_DeviceStats::MAPKEY_CURRENTDATA_STRINGCONTROLCOUNT{ "solarapi_currentdata_stringcontrolcount" };
const std::string Notification_DeviceStats::MAPKEY_CURRENTDATA_METERCOUNT{ "solarapi_currentdata_metercount" };
const std::string Notification_DeviceStats::MAPKEY_CURRENTDATA_POWERFLOWCOUNT{ "solarapi_currentdata_powerflowcount" };
const std::string Notification_DeviceStats::MAPKEY_LOGDATA_DATACOUNT{ "solarapi_logdata_datacount" };
const std::string Notification_DeviceStats::MAPKEY_LOGDATA_ERRORSANDEVENTSCOUNT{ "solarapi_logdata_errorsandeventscount" };

Notification_DeviceStats::Notification_DeviceStats(SymoNotification_PublishPayload::Types::DeviceId device_id) :
	Notification_BaseDeviceStats(device_id)
{
}

Notification_DeviceStats& Notification_DeviceStats::DeviceStats(const Fronius::DeviceStatistics& statistics)
{
	SolarAPI_CurrentData_InverterCount(statistics.SolarAPI_CurrentData_InverterCount);
	SolarAPI_CurrentData_SensorCardCount(statistics.SolarAPI_CurrentData_SensorCardCount);
	SolarAPI_CurrentData_StringControlCount(statistics.SolarAPI_CurrentData_StringControlCount);
	SolarAPI_CurrentData_MeterCount(statistics.SolarAPI_CurrentData_MeterCount);
	SolarAPI_CurrentData_PowerFlowCount(statistics.SolarAPI_CurrentData_PowerFlowCount);
	SolarAPI_LogData_DataCount(statistics.SolarAPI_LogData_DataCount);
	SolarAPI_LogData_ErrorsAndEventsCount(statistics.SolarAPI_LogData_ErrorsAndEventsCount);

	Notification_BaseDeviceStats::DeviceStats(statistics);

	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_CurrentData_InverterCount(const uint64_t& currentdata_invertercount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTDATA_INVERTERCOUNT, currentdata_invertercount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_CurrentData_SensorCardCount(const uint64_t& currentdata_sensorcardcount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTDATA_SENSORCARDCOUNT, currentdata_sensorcardcount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_CurrentData_StringControlCount(const uint64_t& currentdata_stringcontrolcount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTDATA_STRINGCONTROLCOUNT, currentdata_stringcontrolcount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_CurrentData_MeterCount(const uint64_t& currentdata_metercount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTDATA_METERCOUNT, currentdata_metercount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_CurrentData_PowerFlowCount(const uint64_t& currentdata_powerflowcount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTDATA_POWERFLOWCOUNT, currentdata_powerflowcount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_LogData_DataCount(const uint64_t& logdata_datacount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_LOGDATA_DATACOUNT, logdata_datacount);
	return *this;
}

Notification_DeviceStats& Fronius::Notification_DeviceStats::SolarAPI_LogData_ErrorsAndEventsCount(const uint64_t& logdata_errorsandeventscount)
{
	m_ElementsMap.insert_or_assign(MAPKEY_LOGDATA_ERRORSANDEVENTSCOUNT, logdata_errorsandeventscount);
	return *this;
}

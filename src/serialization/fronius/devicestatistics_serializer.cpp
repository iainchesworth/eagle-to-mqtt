#include <boost/log/trivial.hpp>

#include "serialization/fronius/devicestatistics_serializer.h"

using namespace Fronius;

DeviceStatistics_Serializer::DeviceStatistics_Serializer(const DeviceStatistics& ds) :
	ISerializer(ds)
{
}

boost::json::object DeviceStatistics_Serializer::Serialize() const
{
	boost::json::object device_stats;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing Fronius::DeviceStatistics";

	device_stats["LastMessageTimestamp"] = UnixTimepoint::ToString(m_Serializable.LastMessageTimestamp);
	device_stats["MessageCount"] = m_Serializable.MessageCount;
	device_stats["MissingPayloadFields"] = m_Serializable.MissingPayloadFields;
	device_stats["ErrorsWhileProcessing"] = m_Serializable.ErrorsWhileProcessing;
	device_stats["SolarAPI_CurrentData_InverterCount"] = m_Serializable.SolarAPI_CurrentData_InverterCount;
	device_stats["SolarAPI_CurrentData_SensorCardCount"] = m_Serializable.SolarAPI_CurrentData_SensorCardCount;
	device_stats["SolarAPI_CurrentData_StringControlCount"] = m_Serializable.SolarAPI_CurrentData_StringControlCount;
	device_stats["SolarAPI_CurrentData_MeterCount"] = m_Serializable.SolarAPI_CurrentData_MeterCount;
	device_stats["SolarAPI_CurrentData_PowerFlowCount"] = m_Serializable.SolarAPI_CurrentData_PowerFlowCount;
	device_stats["SolarAPI_LogData_DataCount"] = m_Serializable.SolarAPI_LogData_DataCount;
	device_stats["SolarAPI_LogData_ErrorsAndEventsCount"] = m_Serializable.SolarAPI_LogData_ErrorsAndEventsCount;
	device_stats["UnknownMessageCount"] = m_Serializable.UnknownMessageCount;

	return device_stats;
}

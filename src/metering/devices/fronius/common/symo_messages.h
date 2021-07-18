#ifndef SYMO_MESSAGES_H
#define SYMO_MESSAGES_H

#include <boost/property_tree/ptree.hpp>

#include <ostream>
#include <string>

class SymoMessages
{
	static const std::string NOT_SPECIFIED;
	static const std::string SOLARAPI_CURRENTDATA_INVERTER;
	static const std::string SOLARAPI_CURRENTDATA_SENSORCARD;
	static const std::string SOLARAPI_CURRENTDATA_STRINGCONTROL;
	static const std::string SOLARAPI_CURRENTDATA_METER;
	static const std::string SOLARAPI_CURRENTDATA_POWERFLOW;
	static const std::string SOLARAPI_LOGDATA_DATA;
	static const std::string SOLARAPI_LOGDATA_ERRORSANDEVENTS;
	static const std::string UNKNOWN;

public:
	enum class SymoMessageTypes
	{
		NotSpecified,
		SolarAPI_CurrentData_Inverter,
		SolarAPI_CurrentData_SensorCard,
		SolarAPI_CurrentData_StringControl,
		SolarAPI_CurrentData_Meter,
		SolarAPI_CurrentData_PowerFlow,
		SolarAPI_LogData_Data,
		SolarAPI_LogData_ErrorsAndEvents,
		Unknown
	};

public:
	SymoMessages();
	SymoMessages(SymoMessageTypes message_type);
	SymoMessages(const boost::property_tree::ptree& node);

private:
	SymoMessageTypes m_MessageType;

public:
	static SymoMessageTypes FromPayload(const boost::property_tree::ptree& node);
	static std::string ToString(const SymoMessageTypes message_type);

public:
	friend std::ostream& operator<<(std::ostream& os, const SymoMessages& message_type);
};

#endif // SYMO_MESSAGES_H

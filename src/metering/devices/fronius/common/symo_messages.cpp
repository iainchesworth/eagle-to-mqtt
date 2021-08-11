#include <spdlog/spdlog.h>

#include "metering/devices/fronius/common/symo_messages.h"

const std::string SymoMessages::NOT_SPECIFIED{ "Not Specified" };
const std::string SymoMessages::SOLARAPI_CURRENTDATA_INVERTER{ "SolarAPI_CurrentData_Inverter" };
const std::string SymoMessages::SOLARAPI_CURRENTDATA_SENSORCARD{ "SolarAPI_CurrentData_SensorCard" };
const std::string SymoMessages::SOLARAPI_CURRENTDATA_STRINGCONTROL{ "SolarAPI_CurrentData_StringControl" };
const std::string SymoMessages::SOLARAPI_CURRENTDATA_METER{ "SolarAPI_CurrentData_Meter" };
const std::string SymoMessages::SOLARAPI_CURRENTDATA_POWERFLOW{ "SolarAPI_CurrentData_PowerFlow" };
const std::string SymoMessages::SOLARAPI_LOGDATA_DATA{ "SolarAPI_LogData_Data" };
const std::string SymoMessages::SOLARAPI_LOGDATA_ERRORSANDEVENTS{ "SolarAPI_LogData_ErrorsAndEvents" };
const std::string SymoMessages::UNKNOWN{ "Unknown" };

SymoMessages::SymoMessages() :
	SymoMessages(SymoMessageTypes::NotSpecified)
{
}

SymoMessages::SymoMessages(SymoMessageTypes message_type) :
	m_MessageType(message_type)
{
}

SymoMessages::SymoMessages(const boost::property_tree::ptree& node) :
	m_MessageType(FromPayload(node))
{
}

SymoMessages::SymoMessageTypes SymoMessages::FromPayload(const boost::property_tree::ptree& node)
{
	if (const auto scope_node = node.get_optional<std::string>("Head.RequestArguments.Scope"); (!scope_node.is_initialized()) || "System" != scope_node.get())
	{
		spdlog::debug("SymoMessages::FromPayload - cannot find scope node");

		// Check for message payloads that don't have anything in the header.requestarguments...
		return MessageCheck_3(node);
	}
	else if (auto message_type_1 = MessageCheck_1(node); SymoMessageTypes::Unknown != message_type_1)
	{
		return message_type_1;
	}
	else if (auto message_type_2 = MessageCheck_2(node); SymoMessageTypes::Unknown != message_type_2)
	{
		return message_type_2;
	}
	else
	{
		spdlog::debug("SymoMessages::FromPayload - cannot determine message type");
		return SymoMessageTypes::Unknown;
	}
}

std::string SymoMessages::ToString(const SymoMessageTypes message_type)
{
	switch (message_type)
	{
	case SymoMessageTypes::NotSpecified:
		return NOT_SPECIFIED;
	case SymoMessageTypes::SolarAPI_CurrentData_Inverter:
		return SOLARAPI_CURRENTDATA_INVERTER;
	case SymoMessageTypes::SolarAPI_CurrentData_Meter:
		return SOLARAPI_CURRENTDATA_METER;
	case SymoMessageTypes::SolarAPI_CurrentData_PowerFlow:
		return SOLARAPI_CURRENTDATA_POWERFLOW;
	case SymoMessageTypes::SolarAPI_CurrentData_SensorCard:
		return SOLARAPI_CURRENTDATA_SENSORCARD;
	case SymoMessageTypes::SolarAPI_CurrentData_StringControl:
		return SOLARAPI_CURRENTDATA_STRINGCONTROL;
	case SymoMessageTypes::SolarAPI_LogData_Data:
		return SOLARAPI_LOGDATA_DATA;
	case SymoMessageTypes::SolarAPI_LogData_ErrorsAndEvents:
		return SOLARAPI_LOGDATA_ERRORSANDEVENTS;
	case SymoMessageTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

SymoMessages::SymoMessageTypes SymoMessages::MessageCheck_1(const boost::property_tree::ptree& node)
{
	SymoMessageTypes message_type = SymoMessageTypes::Unknown;

	if (const auto query_node = node.get_optional<std::string>("Head.RequestArguments.Query"); !query_node.is_initialized())
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - cannot find query node");
	}
	else if ("Inverter" == query_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - found message: SolarAPI v1 - CurrentData - Inverter");
		message_type = SymoMessageTypes::SolarAPI_CurrentData_Inverter;
	}
	else if ("Meter" == query_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - found message: SolarAPI v1 - CurrentData - Meter");
		message_type = SymoMessageTypes::SolarAPI_CurrentData_Meter;
	}
	else if ("Inverter+SensorCard+Meter" == query_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - found message: SolarAPI v1 - LogData - Data");
		message_type = SymoMessageTypes::SolarAPI_LogData_Data;
	}
	else if ("Errors+Events" == query_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - found message: SolarAPI v1 - Errors And Events");
		message_type = SymoMessageTypes::SolarAPI_LogData_ErrorsAndEvents;
	}
	else
	{
		spdlog::trace("SymoMessages::MessageCheck_1 - cannot determine message type");
	}

	return message_type;
}

SymoMessages::SymoMessageTypes SymoMessages::MessageCheck_2(const boost::property_tree::ptree& node)
{
	SymoMessageTypes message_type = SymoMessageTypes::Unknown;

	if (const auto device_class_node = node.get_optional<std::string>("Head.RequestArguments.DeviceClass"); !device_class_node.is_initialized())
	{
		spdlog::trace("SymoMessages::MessageCheck_2 - cannot find device class node");
	}
	else if ("SensorCard" == device_class_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_2 - found message: SolarAPI v1 - CurrentData - SensorCard");
		message_type = SymoMessageTypes::SolarAPI_CurrentData_SensorCard;
	}
	else if ("StringControl" == device_class_node.get())
	{
		spdlog::trace("SymoMessages::MessageCheck_2 - found message: SolarAPI v1 - CurrentData - StringControl");
		message_type = SymoMessageTypes::SolarAPI_CurrentData_StringControl;
	}
	else
	{
		spdlog::trace("SymoMessages::MessageCheck_2 - cannot determine message type");
	}

	return message_type;
}

SymoMessages::SymoMessageTypes SymoMessages::MessageCheck_3(const boost::property_tree::ptree& node)
{
	SymoMessageTypes message_type = SymoMessageTypes::Unknown;

	if (const auto body_inverters_node = node.get_child_optional("Body.Inverters"); !body_inverters_node.is_initialized())
	{
		spdlog::trace("SymoMessages::MessageCheck_3 - cannot find body.inverters node");
	}
	else
	{
		spdlog::trace("SymoMessages::MessageCheck_2 - found message: SolarAPI v1 - CurrentData - PowerFlow");
		message_type = SymoMessageTypes::SolarAPI_CurrentData_PowerFlow;
	}

	return message_type;
}

std::ostream& operator<<(std::ostream& os, const SymoMessages& message)
{
	os << SymoMessages::ToString(message.m_MessageType);
	return os;
}

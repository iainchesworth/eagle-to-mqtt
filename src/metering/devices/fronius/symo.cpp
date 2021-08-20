#include <date/date.h>
#include <spdlog/spdlog.h>

#include <chrono>
#include <string>

#include "metering/devices/fronius/symo.h"
#include "metering/devices/fronius/common/symo_messages.h"
#include "serialization/fronius/symo_serializer.h"

Symo::Symo() :
	IDevice()
{
}

void Symo::ProcessPayload(const boost::property_tree::ptree& node)
{
	try
	{
		switch (SymoMessages::FromPayload(node))
		{
		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_Inverter:
			spdlog::debug("Processing SolarAPI_CurrentData_Inverter fragment");
			ProcessFragment(SolarApi_CurrentData_Inverter(node));
			++m_Statistics.SolarAPI_CurrentData_InverterCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_SensorCard:
			spdlog::debug("Processing SolarAPI_CurrentData_SensorCard fragment");
			ProcessFragment(SolarApi_CurrentData_SensorCard(node));
			++m_Statistics.SolarAPI_CurrentData_SensorCardCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_StringControl:
			spdlog::debug("Processing SolarAPI_CurrentData_StringControl fragment");
			ProcessFragment(SolarApi_CurrentData_StringControl(node));
			++m_Statistics.SolarAPI_CurrentData_StringControlCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_Meter:
			spdlog::debug("Processing SolarAPI_CurrentData_Meter fragment");
			ProcessFragment(SolarApi_CurrentData_Meter(node));
			++m_Statistics.SolarAPI_CurrentData_MeterCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_PowerFlow:
			spdlog::debug("Processing SolarAPI_CurrentData_PowerFlow fragment");
			ProcessFragment(SolarApi_CurrentData_PowerFlow(node));
			++m_Statistics.SolarAPI_CurrentData_PowerFlowCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_LogData_Data:
			spdlog::debug("Processing SolarAPI_LogData_Data fragment");
			ProcessFragment(SolarApi_LogData_Data(node));
			++m_Statistics.SolarAPI_LogData_DataCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_LogData_ErrorsAndEvents:
			spdlog::debug("Processing SolarAPI_LogData_Data fragment");
			ProcessFragment(SolarApi_LogData_ErrorsAndEvents(node));
			++m_Statistics.SolarAPI_LogData_ErrorsAndEventsCount;
			break;

		default:
			spdlog::debug("Ignoring unhandled message type in upload data set");
			++m_Statistics.UnknownMessageCount;
			break;
		}

		// Increment the total message count
		++m_Statistics.MessageCount;

		// Capture the last message time (i.e. "now").
		m_Statistics.LastMessageTimestamp = std::chrono::system_clock::now();
	}
	catch (const boost::property_tree::ptree_error& pte)
	{
		spdlog::trace("Missing payload field while processing payload...capturing error and re-throwing");
		++m_Statistics.MissingPayloadFields;
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const std::exception& ex)
	{
		spdlog::trace("General error occurred while processing payload...capturing error and re-throwing");
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
}

void Symo::ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes)
{
	// Capture the timestamp for this device payload
	const auto timestamp = header_attributes.get_optional<std::string>("Head.Timestamp");
	if (!timestamp.is_initialized())
	{
		spdlog::warn("Missing expected field (timestamp) in head.timestamp payload");
	}
	else
	{
		std::chrono::time_point<std::chrono::system_clock> message_timestamp;
		std::istringstream iss{ timestamp.get() };
		iss >> date::parse(std::string("%Y-%m-%dT%H:%M:%S%z"), message_timestamp);
	}
}

const Fronius::DeviceStatistics& Symo::Statistics() const
{
	return m_Statistics;
}

const Fronius::EnergyProduction& Symo::EnergyProduction() const
{
	return m_EnergyProduction;
}

boost::json::object Symo::Serialize() const
{
	return Symo_Serializer(*this).Serialize();
}

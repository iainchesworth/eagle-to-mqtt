#include <boost/log/trivial.hpp>
#include <date/date.h>

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
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_CurrentData_Inverter fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_CurrentData_InverterCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_SensorCard:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_CurrentData_SensorCard fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_CurrentData_SensorCardCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_StringControl:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_CurrentData_StringControl fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_CurrentData_StringControlCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_Meter:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_CurrentData_Meter fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_CurrentData_MeterCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_CurrentData_PowerFlow:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_CurrentData_PowerFlow fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_CurrentData_PowerFlowCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_LogData_Data:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_LogData_Data fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_LogData_DataCount;
			break;

		case SymoMessages::SymoMessageTypes::SolarAPI_LogData_ErrorsAndEvents:
			BOOST_LOG_TRIVIAL(debug) << L"Processing SolarAPI_LogData_Data fragment";
			//ProcessFragment(X(Y));
			++m_Statistics.SolarAPI_LogData_ErrorsAndEventsCount;
			break;

		default:
			BOOST_LOG_TRIVIAL(debug) << L"Ignoring unhandled message type in upload data set";
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
		BOOST_LOG_TRIVIAL(trace) << L"Missing payload field while processing payload...capturing error and re-throwing";
		++m_Statistics.MissingPayloadFields;
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(trace) << L"General error occurred while processing payload...capturing error and re-throwing";
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
		BOOST_LOG_TRIVIAL(warning) << L"Missing expected field (timestamp) in head.timestamp payload";
	}
	else
	{
		std::chrono::time_point<std::chrono::system_clock> message_timestamp;
		std::istringstream iss{ timestamp.get() };
		iss >> date::parse(std::string("%Y-%m-%dT%H:%M:%S%z"), message_timestamp);
	}
}

boost::json::object Symo::Serialize() const
{
	return Symo_Serializer(*this).Serialize();
}

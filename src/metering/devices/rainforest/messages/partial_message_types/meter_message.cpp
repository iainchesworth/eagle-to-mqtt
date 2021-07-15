#include "metering/devices/rainforest/messages/partial_message_types/meter_message.h"
#include "metering/types/boolean.h"
#include "metering/types/essential.h"
#include "metering/types/integer.h"
#include "metering/types/optional.h"

MeterMessage::MeterMessage(std::string id, std::string text, Priorities priority, std::chrono::time_point<std::chrono::system_clock> start_time, std::chrono::minutes duration, bool confirmation_required, bool confirmed) :
	m_Id(id),
	m_Text(text),
	m_Priority(priority),
	m_StartTime(start_time),
	m_Duration(duration),
	m_ConfirmationRequired(confirmation_required),
	m_Confirmed(confirmed)
{
}

std::string MeterMessage::Id() const
{
	return m_Id;
}

std::string MeterMessage::Text() const
{
	return m_Text;
}

Priorities MeterMessage::Priority() const
{
	return m_Priority;
}

std::chrono::time_point<std::chrono::system_clock> MeterMessage::ValidFrom() const
{
	return m_StartTime;
}

std::chrono::time_point<std::chrono::system_clock> MeterMessage::ValidTill() const
{
	return m_StartTime + m_Duration;
}

bool MeterMessage::ConfirmationRequired() const
{
	return m_ConfirmationRequired;
}

bool MeterMessage::IsConfirmed() const
{
	return m_Confirmed;
}

MeterMessage MeterMessage::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	auto start_time = IsOptionalWithDefault<uint32_t>(node, "StartTime", 0); // Does not exist in V1 payloads
	auto duration = IsOptionalWithDefault<uint16_t>(node, "Duration", 0);	 // Does not exist in V1 payloads

	auto duration_in_minutes = std::chrono::minutes(duration); // Will default to a duration of "0" if not present.
	auto offset = unsigned_to_signed(start_time);			   // Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto start_time_as_time_point = now + std::chrono::duration<int64_t>(offset);

	// There appears to be a bug where the EAGLE-200 uses "PRI" as the field name not "Priority"
	Priorities priority;

	if (auto raw_priority = IsOptional<Priorities>(node, "Priority"); raw_priority.has_value())
	{
		priority = raw_priority.value();
	}
	else if (auto raw_priority = IsOptional<Priorities>(node, "PRI"); raw_priority.has_value())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Eagle Bug: Priority field uses incorrect field name \"PRI\" (refer to EAGLE-200 API documentation, section 4.6.1)";
		priority = raw_priority.value();
	}
	else
	{
		throw MissingMessageKey("Priority/PRI");
	}

	return MeterMessage(
		IsEssential<std::string>(node, "Id"),
		IsEssential<std::string>(node, "Text"),
		priority,
		start_time_as_time_point,
		duration_in_minutes,
		IsEssential<bool>(node, "ConfirmationRequired"),
		IsEssential<bool>(node, "Confirmed")
	);
}

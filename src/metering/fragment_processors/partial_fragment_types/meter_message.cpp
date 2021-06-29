#include "metering/fragment_processors/partial_fragment_types/meter_message.h"
#include "metering/type_handlers/boolean.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

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
	auto start_time = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("StartTime"); }, "0x00000000");  // Does not exist in V1 payloads
	auto duration = IsOptional<std::string>([&node]() -> std::string { return node.get<std::string>("Duration"); }, "0x0000");		   // Does not exist in V1 payloads

	auto offset = unsigned_to_signed(hex_string_to_uint32_t(start_time));				  // Will default to an offset of "0" if not present.
	auto now = std::chrono::system_clock::now();
	auto start_time_as_time_point = now + std::chrono::duration<int64_t>(offset);
	auto duration_in_minutes = std::chrono::minutes(hex_string_to_uint16_t(duration));	  // Will default to a duration of "0" if not present.

	// There appears to be a bug where the EAGLE-200 uses "PRI" as the field name not "Priority"
	boost::optional<std::string> priority_as_string;
	Priorities priority;

	if (priority_as_string = node.get_optional<std::string>("Priority"); priority_as_string.is_initialized())
	{
		priority = Priorities::FromString(priority_as_string.get());
	}
	else if (priority_as_string = node.get_optional<std::string>("PRI"); priority_as_string.is_initialized())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Eagle Bug: Priority field uses incorrect field name \"PRI\" (refer to EAGLE-200 API documentation, section 4.6.1)";
		priority = Priorities::FromString(priority_as_string.get());
	}
	else
	{
		throw MissingMessageKey("Priority/PRI");
	}

	return MeterMessage(
		IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("Id"); }),
		IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("Text"); }),
		priority,
		start_time_as_time_point,
		duration_in_minutes,
		IsEssential<bool>([&node]() -> bool { return GetValue_Boolean(node, "ConfirmationRequired"); }),
		IsEssential<bool>([&node]() -> bool { return GetValue_Boolean(node, "Confirmed"); })
	);
}

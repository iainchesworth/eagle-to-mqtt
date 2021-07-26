#include <boost/log/trivial.hpp>

#include "exceptions/invalid_priority_value.h"
#include "metering/common/priorities.h"

const std::string Priorities::NOT_SPECIFIED{ "Not Specified" };
const std::string Priorities::LOW{ "Low" };
const std::string Priorities::MEDIUM{ "Medium" };
const std::string Priorities::HIGH{ "High" };
const std::string Priorities::CRITICAL{ "Critical" };
const std::string Priorities::UNKNOWN{ "Unknown" };

Priorities::Priorities() :
	Priorities(PriorityTypes::NotSpecified)
{
}

Priorities::Priorities(PriorityTypes priority) :
	m_Priority(priority)
{
}

Priorities::Priorities(const std::string& priority) :
	m_Priority(FromString(priority))
{
}

Priorities::PriorityTypes Priorities::FromString(const std::string& priority_string)
{
	PriorityTypes priority_type = PriorityTypes::NotSpecified;

	if (0 == priority_string.length())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Invalid Priority provided to converter (zero-length)";
		throw InvalidPriorityValue("Zero-length priority value");
	}
	else if (LOW == priority_string)
	{
		priority_type = PriorityTypes::Low;
	}
	else if (MEDIUM == priority_string)
	{
		priority_type = PriorityTypes::Medium;
	}
	else if (HIGH == priority_string)
	{
		priority_type = PriorityTypes::High;
	}
	else if (CRITICAL == priority_string)
	{
		priority_type = PriorityTypes::Critical;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Priority provided to converter: " << priority_string;
		priority_type = PriorityTypes::Unknown;
	}

	return priority_type;
}

std::string Priorities::ToString(const PriorityTypes priority_type)
{
	switch (priority_type)
	{
	case PriorityTypes::NotSpecified:
		return NOT_SPECIFIED;
	case PriorityTypes::Low:
		return LOW;
	case PriorityTypes::Medium:
		return MEDIUM;
	case PriorityTypes::High:
		return HIGH;
	case PriorityTypes::Critical:
		return CRITICAL;
	case PriorityTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Priorities::operator==(const Priorities& other) const
{
	return (m_Priority == other.m_Priority);
}

bool Priorities::operator==(const PriorityTypes& priority_type) const
{
	return (m_Priority == priority_type);
}

std::ostream& operator<<(std::ostream& os, const Priorities& priority)
{
	os << Priorities::ToString(priority.m_Priority);
	return os;
}

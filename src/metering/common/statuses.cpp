#include <boost/log/trivial.hpp>

#include "exceptions/invalid_status_value.h"
#include "metering/common/statuses.h"

const std::string Statuses::NOT_SPECIFIED{ "Not Specified" };
const std::string Statuses::INITIALIZING{ "Initializing" };
const std::string Statuses::NETWORK_DISCOVERY{ "Network Discovery" };
const std::string Statuses::JOINING{ "Joining" };
const std::string Statuses::JOIN_FAIL{ "Join: Fail" };
const std::string Statuses::JOIN_SUCCESS{ "Join: Success" };
const std::string Statuses::AUTHENTICATING{ "Authenticating" };
const std::string Statuses::AUTHENTICATING_FAIL{ "Authenticating: Fail" };
const std::string Statuses::AUTHENTICATING_SUCCESS{ "Authenticating: Success" };
const std::string Statuses::CONNECTED{ "Connected" };
const std::string Statuses::DISCONNECTED{ "Disconnected" };
const std::string Statuses::REJOINING{ "Rejoining" };
const std::string Statuses::UNKNOWN{ "Unknown" };

Statuses::Statuses() : 
	Statuses(StatusTypes::NotSpecified)
{
}

Statuses::Statuses(StatusTypes status) :
	m_Status(status)
{
}

Statuses::Statuses(const std::string& status) :
	m_Status(FromString(status))
{
}

Statuses::StatusTypes Statuses::FromString(const std::string& status_string)
{
	StatusTypes status_type = StatusTypes::NotSpecified;

	if (0 == status_string.length())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Invalid Status provided to converter (zero-length)";
		throw InvalidStatusValue("Zero-length status value");
	}
	else if (INITIALIZING == status_string)
	{
		status_type = StatusTypes::Initializing;
	}
	else if (NETWORK_DISCOVERY == status_string)
	{
		status_type = StatusTypes::NetworkDiscovery;
	}
	else if (JOINING == status_string)
	{
		status_type = StatusTypes::Joining;
	}
	else if (JOIN_FAIL == status_string)
	{
		status_type = StatusTypes::JoinFail;
	}
	else if (JOIN_SUCCESS == status_string)
	{
		status_type = StatusTypes::JoinSuccess;
	}
	else if (AUTHENTICATING == status_string)
	{
		status_type = StatusTypes::Authenticating;
	}
	else if (AUTHENTICATING_FAIL == status_string)
	{
		status_type = StatusTypes::AuthenticatingFail;
	}
	else if (AUTHENTICATING_SUCCESS == status_string)
	{
		status_type = StatusTypes::AuthenticatingSuccess;
	}
	else if (CONNECTED == status_string)
	{
		status_type = StatusTypes::Connected;
	}
	else if (DISCONNECTED == status_string)
	{
		status_type = StatusTypes::Disconnected;
	}
	else if (REJOINING == status_string)
	{
		status_type = StatusTypes::Rejoining;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Status provided to converter: " << status_string;
		status_type = StatusTypes::Unknown;
	}

	return status_type;
}

std::string Statuses::ToString(const StatusTypes status_type)
{
	switch (status_type)
	{
	case StatusTypes::NotSpecified: 
		return NOT_SPECIFIED;
	case StatusTypes::Initializing: 
		return INITIALIZING;
	case StatusTypes::NetworkDiscovery: 
		return NETWORK_DISCOVERY;
	case StatusTypes::Joining: 
		return JOINING;
	case StatusTypes::JoinFail: 
		return JOIN_FAIL;
	case StatusTypes::JoinSuccess: 
		return JOIN_SUCCESS;
	case StatusTypes::Authenticating: 
		return AUTHENTICATING;
	case StatusTypes::AuthenticatingFail: 
		return AUTHENTICATING_FAIL;
	case StatusTypes::AuthenticatingSuccess: 
		return AUTHENTICATING_SUCCESS;
	case StatusTypes::Connected: 
		return CONNECTED;
	case StatusTypes::Disconnected: 
		return DISCONNECTED;
	case StatusTypes::Rejoining: 
		return REJOINING;
	case StatusTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Statuses::operator==(const Statuses& other) const
{
	return (m_Status == other.m_Status);
}

std::ostream& operator<<(std::ostream& os, const Statuses& status)
{
	os << Statuses::ToString(status.m_Status);
	return os;
}

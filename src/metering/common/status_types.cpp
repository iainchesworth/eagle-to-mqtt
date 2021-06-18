#include <boost/log/trivial.hpp>

#include "metering/common/status_types.h"

StatusTypes status_type_from_string(const std::string& status)
{
	StatusTypes status_type = StatusTypes::NotSpecified;

	if (0 == status.compare("Initializing"))
	{
		status_type = StatusTypes::Initializing;
	}
	else if (0 == status.compare("Network Discovery"))
	{
		status_type = StatusTypes::NetworkDiscovery;
	}
	else if(0 == status.compare("Joining"))
	{
		status_type = StatusTypes::Joining;
	}
	else if(0 == status.compare("Join: Fail"))
	{
		status_type = StatusTypes::JoinFail;
	}
	else if(0 == status.compare("Join: Success"))
	{
		status_type = StatusTypes::JoinSuccess;
	}
	else if(0 == status.compare("Authenticating"))
	{
		status_type = StatusTypes::Authenticating;
	}
	else if(0 == status.compare("Authenticating: Fail"))
	{
		status_type = StatusTypes::AuthenticatingFail;
	}
	else if(0 == status.compare("Authenticating: Success"))
	{
		status_type = StatusTypes::AuthenticatingSuccess;
	}
	else if(0 == status.compare("Connected"))
	{
		status_type = StatusTypes::Connected;
	}
	else if(0 == status.compare("Disconnected"))
	{
		status_type = StatusTypes::Disconnected;
	}
	else if (0 == status.compare("Rejoining"))
	{
		status_type = StatusTypes::Rejoining;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Status provided to converter: " << status;
		status_type = StatusTypes::Unknown;
	}

	return status_type;
}

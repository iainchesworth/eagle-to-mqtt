#ifndef STATUS_TYPES_H
#define STATUS_TYPES_H

#include <string>

enum class StatusTypes
{
	NotSpecified,
	Initializing,
	NetworkDiscovery,
	Joining,
	JoinFail,
	JoinSuccess,
	Authenticating,
	AuthenticatingFail,
	AuthenticatingSuccess,
	Connected,
	Disconnected,
	Rejoining,
	Unknown
};

StatusTypes status_type_from_string(const std::string& status);

#endif // STATUS_TYPES_H

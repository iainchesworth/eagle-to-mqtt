#ifndef STATUS_H
#define STATUS_H

#include <ostream>
#include <string>

class Statuses
{
	static const std::string NOT_SPECIFIED;
	static const std::string INITIALIZING;
	static const std::string NETWORK_DISCOVERY;
	static const std::string JOINING;
	static const std::string JOIN_FAIL;
	static const std::string JOIN_SUCCESS;
	static const std::string AUTHENTICATING;
	static const std::string AUTHENTICATING_FAIL;
	static const std::string AUTHENTICATING_SUCCESS;
	static const std::string CONNECTED;
	static const std::string DISCONNECTED;
	static const std::string REJOINING;
	static const std::string UNKNOWN;

public:
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

public:
	Statuses();
	Statuses(StatusTypes status);
	Statuses(const std::string& status);

private:
	StatusTypes m_Status;

public:
	static StatusTypes FromString(const std::string& status_string);
	static std::string ToString(const StatusTypes status_type);

public:
	bool operator==(const Statuses& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Statuses& status);
};

#endif // STATUS_H

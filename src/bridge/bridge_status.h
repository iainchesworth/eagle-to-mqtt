#ifndef BRIDGE_STATUS_H
#define BRIDGE_STATUS_H

#include <ostream>
#include <string>

class BridgeStatus
{
	static const std::string NOT_SPECIFIED;
	static const std::string ONLINE;
	static const std::string OFFLINE;
	static const std::string UNKNOWN;

public:
	enum class BridgeStatusTypes
	{
		NotSpecified,
		Online,
		Offline,
		Unknown
	};

public:
	BridgeStatus();
	explicit BridgeStatus(BridgeStatusTypes status);
	explicit BridgeStatus(const std::string& status);

private:
	BridgeStatusTypes m_Status;

public:
	static BridgeStatusTypes FromString(const std::string& status_string);
	static std::string ToString(const BridgeStatusTypes status_type);

public:
	bool operator==(const BridgeStatus& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const BridgeStatus& bridge_status);
};

#endif // BRIDGE_STATUS_H

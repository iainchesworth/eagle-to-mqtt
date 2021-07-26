#include <boost/log/trivial.hpp>

#include "bridge/bridge_status.h"
#include "exceptions/invalid_bridge_status_value.h"

const std::string BridgeStatus::NOT_SPECIFIED{ "NotSpecified" };
const std::string BridgeStatus::ONLINE{ "Online" };
const std::string BridgeStatus::OFFLINE{ "Offline" };
const std::string BridgeStatus::UNKNOWN{ "Unknown" };

BridgeStatus::BridgeStatus() :
	BridgeStatus(BridgeStatusTypes::NotSpecified)
{
}

BridgeStatus::BridgeStatus(BridgeStatusTypes status) :
	m_Status(status)
{
}

BridgeStatus::BridgeStatus(const std::string& status) :
	m_Status(FromString(status))
{

}

BridgeStatus::BridgeStatusTypes BridgeStatus::FromString(const std::string& status_string)
{
	BridgeStatusTypes status_type = BridgeStatusTypes::NotSpecified;

	if (0 == status_string.length())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Invalid Bridge Status provided to converter (zero-length)";
		throw InvalidBridgeStatusValue("Zero-length priority value");
	}
	else if (ONLINE == status_string)
	{
		status_type = BridgeStatusTypes::Online;
	}
	else if (OFFLINE == status_string)
	{
		status_type = BridgeStatusTypes::Offline;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Bridge Status provided to converter: " << status_string;
		status_type = BridgeStatusTypes::Unknown;
	}

	return status_type;
}

std::string BridgeStatus::ToString(const BridgeStatusTypes status_type)
{
	switch (status_type)
	{
	case BridgeStatusTypes::NotSpecified:
		return NOT_SPECIFIED;
	case BridgeStatusTypes::Online:
		return ONLINE;
	case BridgeStatusTypes::Offline:
		return OFFLINE;
	case BridgeStatusTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool BridgeStatus::operator==(const BridgeStatus& other) const
{
	return (m_Status == other.m_Status);
}

bool BridgeStatus::operator==(const BridgeStatusTypes& bridge_status_type) const
{
	return (m_Status == bridge_status_type);
}

std::ostream& operator<<(std::ostream& os, const BridgeStatus& bridge_status)
{
	os << BridgeStatus::ToString(bridge_status.m_Status);
	return os;
}

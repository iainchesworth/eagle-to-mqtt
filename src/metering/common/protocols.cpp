#include <spdlog/spdlog.h>

#include "exceptions/invalid_status_value.h"
#include "metering/common/protocols.h"

const std::string Protocols::NOT_SPECIFIED{ "Not Specified" };
const std::string Protocols::ZIGBEE{ "Zigbee" };
const std::string Protocols::UNKNOWN{ "Unknown" };

Protocols::Protocols() :
	Protocols(ProtocolTypes::NotSpecified)
{
}

Protocols::Protocols(ProtocolTypes protocol) :
	m_Protocol(protocol)
{
}

Protocols::Protocols(const std::string& protocol) :
	m_Protocol(FromString(protocol))
{
}

Protocols::ProtocolTypes Protocols::FromString(const std::string& protocol_string)
{
	ProtocolTypes protocol_type = ProtocolTypes::NotSpecified;

	if (0 == protocol_string.length())
	{
		spdlog::warn("Invalid Protocol provided to converter (zero-length)");
		throw InvalidStatusValue("Zero-length protocol value");
	}
	else if (ZIGBEE == protocol_string)
	{
		protocol_type = ProtocolTypes::Zigbee;
	}
	else
	{
		spdlog::warn("Unknown Protocol provided to converter: {}", protocol_string);
		protocol_type = ProtocolTypes::Unknown;
	}

	return protocol_type;
}

std::string Protocols::ToString(const ProtocolTypes protocol_type)
{
	switch (protocol_type)
	{
	case ProtocolTypes::NotSpecified:
		return NOT_SPECIFIED;
	case ProtocolTypes::Zigbee:
		return ZIGBEE;
	case ProtocolTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Protocols::operator==(const Protocols& other) const
{
	return (m_Protocol == other.m_Protocol);
}

bool Protocols::operator==(const ProtocolTypes& protocol_type) const
{
	return (m_Protocol == protocol_type);
}

std::ostream& operator<<(std::ostream& os, const Protocols& protocol)
{
	os << protocol.ToString(protocol.m_Protocol);
	return os;
}

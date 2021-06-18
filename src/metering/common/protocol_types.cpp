#include <boost/log/trivial.hpp>

#include "metering/common/protocol_types.h"

ProtocolTypes protocol_type_from_string(const std::string& protocol)
{
	ProtocolTypes protocol_type = ProtocolTypes::NotSpecified;

	if (0 == protocol.compare("Zigbee"))
	{
		protocol_type = ProtocolTypes::Zigbee;
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown Protocol type provided to converter: " << protocol;
		protocol_type = ProtocolTypes::Unknown;
	}

	return protocol_type;
}

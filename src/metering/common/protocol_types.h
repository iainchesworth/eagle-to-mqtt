#ifndef PROTOCOL_TYPES_H
#define PROTOCOL_TYPES_H

#include <string>

enum class ProtocolTypes
{
	NotSpecified,
	Zigbee,
	Unknown
};

ProtocolTypes protocol_type_from_string(const std::string& protocol);

#endif // PROTOCOL_TYPES_H

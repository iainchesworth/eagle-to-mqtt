#ifndef INVALID_BRIDGE_STATUS_VALUE_H
#define INVALID_BRIDGE_STATUS_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidBridgeStatusValue : public InvalidValue
{
public:
	explicit InvalidBridgeStatusValue(const std::string& reason_for_invalid_value);
};

#endif // INVALID_BRIDGE_STATUS_VALUE_H

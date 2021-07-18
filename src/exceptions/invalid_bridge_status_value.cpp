#include "exceptions/invalid_bridge_status_value.h"

InvalidBridgeStatusValue::InvalidBridgeStatusValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

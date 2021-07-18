#include "exceptions/invalid_priority_value.h"

InvalidPriorityValue::InvalidPriorityValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

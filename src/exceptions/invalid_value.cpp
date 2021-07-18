#include "exceptions/invalid_value.h"

InvalidValue::InvalidValue(const std::string& reason_for_invalid_value) :
	std::runtime_error(reason_for_invalid_value)
{
}

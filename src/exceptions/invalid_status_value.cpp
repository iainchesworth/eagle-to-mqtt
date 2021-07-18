#include "exceptions/invalid_status_value.h"

InvalidStatusValue::InvalidStatusValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

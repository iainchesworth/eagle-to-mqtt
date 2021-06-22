#include "exceptions/invalid_status_value.h"

InvalidStatusValue::InvalidStatusValue(std::string reason_for_invalid_value) :
	std::runtime_error(reason_for_invalid_value)
{
}

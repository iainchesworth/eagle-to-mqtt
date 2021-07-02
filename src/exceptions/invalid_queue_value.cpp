#include "exceptions/invalid_queue_value.h"

InvalidQueueValue::InvalidQueueValue(std::string reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

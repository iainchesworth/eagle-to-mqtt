#ifndef INVALID_QUEUE_VALUE_H
#define INVALID_QUEUE_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidQueueValue : public InvalidValue
{
public:
	InvalidQueueValue(std::string reason_for_invalid_value);
};

#endif // INVALID_QUEUE_VALUE_H

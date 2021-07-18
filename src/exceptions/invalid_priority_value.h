#ifndef INVALID_PRIORITY_VALUE_H
#define INVALID_PRIORITY_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidPriorityValue : public InvalidValue
{
public:
	explicit InvalidPriorityValue(const std::string& reason_for_invalid_value);
};

#endif // INVALID_PRIORITY_VALUE_H

#ifndef INVALID_STATUS_VALUE_H
#define INVALID_STATUS_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidStatusValue : public InvalidValue
{
public:
	explicit InvalidStatusValue(const std::string& reason_for_invalid_value);
};

#endif // INVALID_STATUS_VALUE_H

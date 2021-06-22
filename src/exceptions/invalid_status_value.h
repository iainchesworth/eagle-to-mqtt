#ifndef INVALID_STATUS_VALUE_H
#define INVALID_STATUS_VALUE_H

#include <stdexcept>
#include <string>

class InvalidStatusValue : public std::runtime_error
{
public:
	InvalidStatusValue(std::string reason_for_invalid_value);
};

#endif // INVALID_STATUS_VALUE_H

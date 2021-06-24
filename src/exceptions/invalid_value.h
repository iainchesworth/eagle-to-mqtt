#ifndef INVALID_VALUE_H
#define INVALID_VALUE_H

#include <stdexcept>
#include <string>

class InvalidValue : public std::runtime_error
{
public:
	InvalidValue(std::string reason_for_invalid_value);
};

#endif // INVALID_VALUE_H

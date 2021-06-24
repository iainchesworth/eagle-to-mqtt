#ifndef INVALID_MESSAGE_VALUE_H
#define INVALID_MESSAGE_VALUE_H

#include <stdexcept>
#include <string_view>

#include "exceptions/invalid_value.h"

class InvalidMessageValue : public InvalidValue
{
public:
	InvalidMessageValue(std::string_view missing_key);

public:
	const std::string_view InvalidValueKey() const;

private:
	const std::string_view m_InvalidValueKey;
};

#endif // INVALID_MESSAGE_VALUE_H

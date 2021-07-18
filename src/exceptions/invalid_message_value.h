#ifndef INVALID_MESSAGE_VALUE_H
#define INVALID_MESSAGE_VALUE_H

#include <stdexcept>
#include <string>

#include "exceptions/invalid_value.h"

class InvalidMessageValue : public InvalidValue
{
public:
	InvalidMessageValue(const std::string& missing_key);

public:
	const std::string InvalidValueKey() const;

private:
	const std::string m_InvalidValueKey;
};

#endif // INVALID_MESSAGE_VALUE_H

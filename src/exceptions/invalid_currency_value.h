#ifndef INVALID_CURRENCY_VALUE_H
#define INVALID_CURRENCY_VALUE_H

#include <stdexcept>
#include <string>

class InvalidCurrencyValue : public std::runtime_error
{
public:
	InvalidCurrencyValue(std::string reason_for_invalid_value);
};

#endif // INVALID_CURRENCY_VALUE_H

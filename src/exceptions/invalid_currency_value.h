#ifndef INVALID_CURRENCY_VALUE_H
#define INVALID_CURRENCY_VALUE_H

#include <string>

#include "exceptions/invalid_value.h"

class InvalidCurrencyValue : public InvalidValue
{
public:
	InvalidCurrencyValue(std::string reason_for_invalid_value);
};

#endif // INVALID_CURRENCY_VALUE_H

#include "exceptions/invalid_currency_value.h"

InvalidCurrencyValue::InvalidCurrencyValue(std::string reason_for_invalid_value) :
	std::runtime_error(reason_for_invalid_value)
{
}

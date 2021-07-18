#include "exceptions/invalid_currency_value.h"

InvalidCurrencyValue::InvalidCurrencyValue(const std::string& reason_for_invalid_value) :
	InvalidValue(reason_for_invalid_value)
{
}

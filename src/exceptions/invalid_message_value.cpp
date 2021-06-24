#include "exceptions/invalid_message_value.h"

InvalidMessageValue::InvalidMessageValue(std::string_view invalid_value_key) :
	InvalidValue("Requested key's value is invalid"),
	m_InvalidValueKey(invalid_value_key)
{
}

const std::string_view InvalidMessageValue::InvalidValueKey() const
{
	return m_InvalidValueKey;
}

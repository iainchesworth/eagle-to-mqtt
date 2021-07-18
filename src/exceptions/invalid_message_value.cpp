#include "exceptions/invalid_message_value.h"

InvalidMessageValue::InvalidMessageValue(const std::string& invalid_value_key) :
	InvalidValue("Requested key's value is invalid"),
	m_InvalidValueKey(invalid_value_key)
{
}

const std::string InvalidMessageValue::InvalidValueKey() const
{
	return m_InvalidValueKey;
}

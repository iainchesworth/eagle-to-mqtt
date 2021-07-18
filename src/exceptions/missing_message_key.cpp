#include "exceptions/missing_message_key.h"

MissingMessageKey::MissingMessageKey(const std::string& missing_key) :
	std::runtime_error("Requested key is missing from message payload"),
	m_MissingKey(missing_key)
{
}

const std::string MissingMessageKey::MissingKey() const
{
	return m_MissingKey;
}

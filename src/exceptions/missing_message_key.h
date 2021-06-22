#ifndef MISSING_MESSAGE_KEY_H
#define MISSING_MESSAGE_KEY_H

#include <stdexcept>
#include <string_view>

class MissingMessageKey : public std::runtime_error
{
public:
	MissingMessageKey(std::string_view missing_key);

public:
	const std::string_view MissingKey() const;

private:
	const std::string_view m_MissingKey;
};

#endif // MISSING_MESSAGE_KEY_H

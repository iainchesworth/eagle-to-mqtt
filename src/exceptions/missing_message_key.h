#ifndef MISSING_MESSAGE_KEY_H
#define MISSING_MESSAGE_KEY_H

#include <stdexcept>
#include <string>

class MissingMessageKey : public std::runtime_error
{
public:
	MissingMessageKey(const std::string& missing_key);

public:
	const std::string MissingKey() const;

private:
	const std::string m_MissingKey;
};

#endif // MISSING_MESSAGE_KEY_H

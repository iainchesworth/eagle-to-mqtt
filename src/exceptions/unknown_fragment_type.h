#ifndef UNKNOWN_FRAGMENT_TYPE_H
#define UNKNOWN_FRAGMENT_TYPE_H

#include <stdexcept>
#include <string>

class UnknownFragmentType : public std::runtime_error
{
public:
	explicit UnknownFragmentType(const std::string& unknown_fragment);

public:
	const std::string Fragment() const;

private:
	const std::string m_UnknownFragment;
};

#endif // UNKNOWN_FRAGMENT_TYPE_H

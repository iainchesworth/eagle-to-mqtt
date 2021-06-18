#ifndef UNKNOWN_FRAGMENT_TYPE_H
#define UNKNOWN_FRAGMENT_TYPE_H

#include <stdexcept>
#include <string_view>

class UnknownFragmentType : public std::runtime_error
{
public:
	UnknownFragmentType(const std::string_view unknown_fragment);

public:
	const std::string_view Fragment() const;

private:
	const std::string_view m_UnknownFragment;
};

#endif // UNKNOWN_FRAGMENT_TYPE_H

#include "exceptions/unknown_fragment_type.h"

UnknownFragmentType::UnknownFragmentType(const std::string unknown_fragment) :
	std::runtime_error("Failed to match fragment type to known value"),
	m_UnknownFragment(unknown_fragment)
{
}

const std::string UnknownFragmentType::Fragment() const
{
	return m_UnknownFragment;
}

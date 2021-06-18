#include "exceptions/unknown_fragment_type.h"

UnknownFragmentType::UnknownFragmentType(const std::string_view unknown_fragment) : 
	std::runtime_error("Failed to match fragment type to known value"),
	m_UnknownFragment(unknown_fragment)
{
}

const std::string_view UnknownFragmentType::Fragment() const
{
	return m_UnknownFragment;
}

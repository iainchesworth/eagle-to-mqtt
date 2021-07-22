#ifndef OPTIONS_OPTION_CONFLICT_H
#define OPTIONS_OPTION_CONFLICT_H

#include <stdexcept>

class Options_OptionConflict : public std::logic_error
{
public:
	explicit Options_OptionConflict(const std::string& conflict_message);
};

#endif // OPTIONS_OPTION_CONFLICT_H

#include "exceptions/options_option_conflict.h"

Options_OptionConflict::Options_OptionConflict(const std::string& conflict_message) :
	std::logic_error(conflict_message)
{
}

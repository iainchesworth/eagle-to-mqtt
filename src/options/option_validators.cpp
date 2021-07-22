#include <string>

#include "exceptions/options_option_conflict.h"
#include "options/option_validators.h"

void Validator_ConflictingOptions(const boost::program_options::variables_map& vm, const char* opt1, const char* opt2)
{
	if (vm.count(opt1) && !vm[opt1].defaulted() && vm.count(opt2) && !vm[opt2].defaulted())
	{
		throw Options_OptionConflict(std::string("Conflicting options '") + opt1 + "' and '" + opt2 + "'.");
	}
}

void Validator_OptionDependency(const boost::program_options::variables_map& vm, const char* for_what, const char* required_option)
{
	if (vm.count(for_what) && !vm[for_what].defaulted())
	{
		if (vm.count(required_option) == 0 || vm[required_option].defaulted())
		{
			throw std::logic_error(std::string("Option '") + for_what + "' requires option '" + required_option + "'.");
		}
	}
}

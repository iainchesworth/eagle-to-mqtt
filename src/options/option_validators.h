#ifndef OPTION_VALIDATORS_H
#define OPTION_VALIDATORS_H

#include <boost/program_options/variables_map.hpp>

void Validator_ConflictingOptions(const boost::program_options::variables_map& vm, const char* opt1, const char* opt2);
void Validator_OptionDependency(const boost::program_options::variables_map& vm, const char* for_what, const char* required_option);

#endif // OPTION_VALIDATORS_H

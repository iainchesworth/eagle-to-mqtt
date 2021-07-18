#ifndef INVALID_NUMBER_CONVERSION_H
#define INVALID_NUMBER_CONVERSION_H

#include <stdexcept>
#include <string>

class InvalidNumberConversion : public std::runtime_error
{
public:
	explicit InvalidNumberConversion(const std::string& reason_for_invalid_conversion);
};

#endif // INVALID_NUMBER_CONVERSION_H

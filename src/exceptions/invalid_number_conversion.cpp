#include "exceptions/invalid_number_conversion.h"

InvalidNumberConversion::InvalidNumberConversion(const std::string& reason_for_invalid_conversion) :
	std::runtime_error(reason_for_invalid_conversion)
{
}

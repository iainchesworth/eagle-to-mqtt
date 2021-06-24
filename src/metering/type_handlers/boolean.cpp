#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>

#include <stdexcept>

#include "exceptions/invalid_value.h"
#include "exceptions/missing_message_key.h"
#include "metering/type_handlers/boolean.h"

bool GetValue_Boolean(const boost::property_tree::ptree& node, const std::string& key)
{
	boost::optional<std::string> value_as_string;
	bool value;

	if (0 == key.length())
	{
		throw std::invalid_argument("Key name is invalid (zero-length string)");
	}
	else if (value_as_string = node.get_optional<std::string>(key); !value_as_string.is_initialized())
	{
		throw MissingMessageKey(key);
	}
	else
	{
		// Attempt to turn a string into a boolean with the following mapping
		//
		//    - Y or N		  --> true or false
		//    - T or F		  --> true or false
		//    - TRUE or FALSE --> true or false
		//    - 1 or 0		  --> true or false
		//
		// NOTE: All comparisons are done in UPPERCASE...

		static const std::string TRUE_ENCODING_1{ "Y" };
		static const std::string TRUE_ENCODING_2{ "T" };
		static const std::string TRUE_ENCODING_3{ "TRUE" };
		static const std::string TRUE_ENCODING_4{ "1" };

		static const std::string FALSE_ENCODING_1{ "N" };
		static const std::string FALSE_ENCODING_2{ "F" };
		static const std::string FALSE_ENCODING_3{ "FALSE" };
		static const std::string FALSE_ENCODING_4{ "0" };

		const std::string uppercase_value_as_string = boost::algorithm::to_upper_copy(value_as_string.get());

		if (0 == uppercase_value_as_string.length())
		{

		}
		else if (
			(0 == uppercase_value_as_string.compare(TRUE_ENCODING_1)) ||
			(0 == uppercase_value_as_string.compare(TRUE_ENCODING_2)) ||
			(0 == uppercase_value_as_string.compare(TRUE_ENCODING_3)) ||
			(0 == uppercase_value_as_string.compare(TRUE_ENCODING_4)))
		{
			value = true;
		}
		else if (
			(0 == uppercase_value_as_string.compare(FALSE_ENCODING_1)) ||
			(0 == uppercase_value_as_string.compare(FALSE_ENCODING_2)) ||
			(0 == uppercase_value_as_string.compare(FALSE_ENCODING_3)) ||
			(0 == uppercase_value_as_string.compare(FALSE_ENCODING_4)))
		{
			value = false;
		}
		else
		{
			// Okay, there's something weird going on
			BOOST_LOG_TRIVIAL(warning) << L"Invalid value provided to boolean converter...cannot convert";
			throw InvalidValue("Invalid value provided to boolean converter");
		}
	}

	return value;
}

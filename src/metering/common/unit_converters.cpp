#include <boost/log/trivial.hpp>

#include <iomanip>
#include <sstream>

#include "metering/common/unit_converters.h"

template<std::size_t HEX_STRING_LENGTH, typename INTEGER_TYPE>
INTEGER_TYPE hex_string_to_integer(const std::string& hex_string)
{
	const uint32_t MAX_HEX_STRING_LENGTH = HEX_STRING_LENGTH;
	if (MAX_HEX_STRING_LENGTH < hex_string.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received hex string that exceeds expected length - was " << hex_string.length() << "; expected " << MAX_HEX_STRING_LENGTH;
	}

	std::istringstream input(hex_string);
	INTEGER_TYPE output;
	input >> std::hex >> output;

	return output;
}

uint64_t hex_string_to_uint64_t(const std::string& hex_string)
{
	return hex_string_to_integer<18, uint64_t>(hex_string);
}

uint32_t hex_string_to_uint32_t(const std::string& hex_string)
{
	return hex_string_to_integer<10, uint32_t>(hex_string);
}

uint16_t hex_string_to_uint16_t(const std::string& hex_string)
{
	return hex_string_to_integer<6, uint16_t>(hex_string);
}

uint8_t hex_string_to_uint8_t(const std::string& hex_string)
{
	return hex_string_to_integer<4, uint8_t>(hex_string);
}

std::chrono::time_point<std::chrono::system_clock> hex_string_to_timepoint(const std::string& hex_string)
{
	std::tm tm = {};
	std::stringstream ss("Jan 1 2000 00:00:00");
	ss >> std::get_time(&tm, "%b %d %Y %H:%M:%S");
	auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));

	const uint32_t MAX_HEX_STRING_LENGTH = 10; // 0x12345678 is the maximum length
	if (MAX_HEX_STRING_LENGTH < hex_string.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received timestamp hex string that exceeds expected length - was " << hex_string.length() << "; expected " << MAX_HEX_STRING_LENGTH;
	}

	std::istringstream input(hex_string);
	uint32_t output;
	input >> std::hex >> output;

	return (tp + std::chrono::seconds(output));
}

bool string_to_bool(const std::string& string, bool default_on_error)
{
	const uint32_t MAX_STRING_LENGTH = 1; // "Y" or "N" is the maximum length and content.
	if (MAX_STRING_LENGTH < string.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received boolean string that exceeds expected length - was " << string.length() << "; expected " << MAX_STRING_LENGTH;
	}

	bool output = default_on_error;

	if (0 == string.length())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Received zero-length string value to convert to boolean";
	}
	else
	{
		switch (std::toupper(string[0]))
		{
		case 'Y':
			output = true;
			break;

		case 'N':
			output = false;
			break;

		default:
			BOOST_LOG_TRIVIAL(warning) << L"Received invalid string value to convert to boolean";
			break;
		}
	}

	return output;
}

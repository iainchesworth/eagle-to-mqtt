#include <boost/log/trivial.hpp>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include "exceptions/invalid_number_conversion.h"
#include "metering/common/unit_converters.h"

template<std::size_t HEX_STRING_LENGTH, typename INTEGER_TYPE>
INTEGER_TYPE hex_string_to_unsigned_integer(const std::string& hex_string)
{
	const uint32_t MAX_HEX_STRING_LENGTH = HEX_STRING_LENGTH;
	if (MAX_HEX_STRING_LENGTH < hex_string.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received hex string that exceeds expected length - was " << hex_string.length() << "; expected " << MAX_HEX_STRING_LENGTH;
	}

	try
	{
		auto converted_value = std::stoull(hex_string, nullptr, 16);
		if (std::numeric_limits<INTEGER_TYPE>::max() < converted_value)
		{
			BOOST_LOG_TRIVIAL(warning) << L"Invalid number conversion performed; too large for destination type";
			throw InvalidNumberConversion(std::string("Invalid number conversion performed: cannot fit ") + hex_string + std::string(" into ") + typeid(INTEGER_TYPE).name());
		}

		return converted_value;
	}
	catch (const std::invalid_argument& ex_ia)
	{
		BOOST_LOG_TRIVIAL(debug) << L"Failed while processing hex string (argument was invalid)";
		BOOST_LOG_TRIVIAL(debug) << L"Invalid hex string (invalid_argument exception) was: " << hex_string;
		throw;
	}
}

uint64_t hex_string_to_uint64_t(const std::string& hex_string)
{
	return hex_string_to_unsigned_integer<18, uint64_t>(hex_string);
}

uint32_t hex_string_to_uint32_t(const std::string& hex_string)
{
	return hex_string_to_unsigned_integer<10, uint32_t>(hex_string);
}

uint16_t hex_string_to_uint16_t(const std::string& hex_string)
{
	return hex_string_to_unsigned_integer<6, uint16_t>(hex_string);
}

uint8_t hex_string_to_uint8_t(const std::string& hex_string)
{
	return hex_string_to_unsigned_integer<4, uint8_t>(hex_string);
}

template<typename SIGNED_TYPE, typename UNSIGNED_TYPE>
SIGNED_TYPE unsigned_to_signed(UNSIGNED_TYPE raw_value)
{
	SIGNED_TYPE converted_value;

	if (std::numeric_limits<SIGNED_TYPE>::max() >= raw_value)
	{
		converted_value = static_cast<SIGNED_TYPE>(raw_value);
	}
	else if (std::numeric_limits<SIGNED_TYPE>::min() <= raw_value)
	{
		converted_value = -(static_cast<SIGNED_TYPE>(~raw_value) - 1);
	}
	else
	{
		converted_value = std::numeric_limits<SIGNED_TYPE>::min();
	}

	return converted_value;
}

int64_t unsigned_to_signed(uint64_t value)
{
	return unsigned_to_signed<int64_t, uint64_t>(value);
}

int32_t unsigned_to_signed(uint32_t value)
{
	return unsigned_to_signed<int32_t, uint32_t>(value);
}

int16_t unsigned_to_signed(uint16_t value)
{
	return unsigned_to_signed<int16_t, uint16_t>(value);
}

int8_t unsigned_to_signed(uint8_t value)
{
	return unsigned_to_signed<int8_t, uint8_t>(value);
}

timepoint_from_jan2000 hex_string_to_timepoint_since_jan2000(const std::string& hex_string)
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

timepoint_from_epoch hex_string_to_timepoint_since_epoch(const std::string& hex_string)
{
	const uint32_t MAX_HEX_STRING_LENGTH = 11; // 1234567890s is the maximum length
	if (MAX_HEX_STRING_LENGTH < hex_string.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received timestamp hex string that exceeds expected length - was " << hex_string.length() << "; expected " << MAX_HEX_STRING_LENGTH;
	}

	std::istringstream input(std::string(hex_string.substr(0, hex_string.length() - 1))); // Trim the "s" from the end and pass that back into the input.
	uint32_t output;
	input >> std::hex >> output;

	// Convert the duration (which is in seconds) to a time_point offset "that duration" from 01/01/1970.
	auto duration_since_epoch = std::chrono::duration<uint32_t, std::ratio<1>>(output);
	return std::chrono::time_point<std::chrono::system_clock>(duration_since_epoch);
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

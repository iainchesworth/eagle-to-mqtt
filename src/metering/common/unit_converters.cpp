#include <spdlog/spdlog.h>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

#include "exceptions/invalid_number_conversion.h"
#include "metering/common/unit_converters.h"

template<std::size_t HEX_STRING_LENGTH, typename INTEGER_TYPE>
INTEGER_TYPE hex_string_to_unsigned_integer(const std::string& hex_string)
{
	if (0 == hex_string.length())
	{
		spdlog::warn("Invalid number conversion performed; zero-length string provided");
		throw InvalidNumberConversion(std::string("Invalid number conversion performed: zero-length source"));
	}
	else if (const uint32_t MAX_HEX_STRING_LENGTH = HEX_STRING_LENGTH; MAX_HEX_STRING_LENGTH < hex_string.length())
	{
		spdlog::warn("Received hex string that exceeds expected length - was {}; expected {}", hex_string.length(), MAX_HEX_STRING_LENGTH);
		throw InvalidNumberConversion(std::string("Invalid number conversion performed: invalid length source"));
	}
	else
	{
		try
		{
			auto converted_value = std::stoull(hex_string, nullptr, 16);
			if (std::numeric_limits<INTEGER_TYPE>::max() < converted_value)
			{
				spdlog::warn("Invalid number conversion performed; too large for destination type");
				throw InvalidNumberConversion(std::string("Invalid number conversion performed: cannot fit ") + hex_string + std::string(" into ") + typeid(INTEGER_TYPE).name());
			}

			return static_cast<INTEGER_TYPE>(converted_value);
		}
		catch (const std::invalid_argument& ex_ia)
		{
			spdlog::debug("Failed while processing hex string (argument was invalid)");
			spdlog::debug("Invalid hex string (invalid_argument exception) was: {}", hex_string);
			throw;
		}
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

std::chrono::time_point<std::chrono::system_clock> hex_string_to_timepoint(const std::string& hex_string)
{
	if (const uint32_t MAX_HEX_STRING_LENGTH = 10; MAX_HEX_STRING_LENGTH < hex_string.length()) // 0x12345678 is the maximum length
	{
		spdlog::debug("Received timestamp hex string that exceeds expected length - was {}; expected {}", hex_string.length(), MAX_HEX_STRING_LENGTH);
	}

	std::istringstream input(hex_string);
	uint32_t output;
	input >> std::hex >> output;

	return std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(output));
}

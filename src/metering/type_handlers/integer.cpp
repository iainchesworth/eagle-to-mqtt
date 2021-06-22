#include <boost/log/trivial.hpp>

#include <functional>
#include <stdexcept>

#include "exceptions/missing_message_key.h"
#include "metering/common/unit_converters.h"
#include "metering/type_handlers/integer.h"

//
// COMMON FUNCTIONS
//

template<typename INTEGER_TYPE>
INTEGER_TYPE GetValue(const boost::property_tree::ptree& node, const std::string& key, std::function<INTEGER_TYPE(const std::string& value)> converter)
{
	boost::optional<std::string> value_as_string;
	INTEGER_TYPE value;

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
		value = converter(value_as_string.get());
	}

	return value;
}

//
// UNSIGNED INTEGER
//

uint64_t GetValue_UInt64(const boost::property_tree::ptree& node, const std::string& key, std::function<uint64_t(const std::string& value)> converter)
{
	return GetValue<uint64_t>(node, key, converter);
}

uint32_t GetValue_UInt32(const boost::property_tree::ptree& node, const std::string& key, std::function<uint32_t(const std::string& value)> converter)
{
	return GetValue<uint32_t>(node, key, converter);
}

uint16_t GetValue_UInt16(const boost::property_tree::ptree& node, const std::string& key, std::function<uint16_t(const std::string& value)> converter)
{
	return GetValue<uint16_t>(node, key, converter);
}

uint8_t GetValue_UInt8(const boost::property_tree::ptree& node, const std::string& key, std::function<uint8_t(const std::string& value)> converter)
{
	return GetValue<uint8_t>(node, key, converter);
}

//
// SIGNED INTEGER
//

int64_t GetValue_Int64(const boost::property_tree::ptree& node, const std::string& key)
{
	return unsigned_to_signed(GetValue_UInt64(node, key));
}

int32_t GetValue_Int32(const boost::property_tree::ptree& node, const std::string& key)
{
	return unsigned_to_signed(GetValue_UInt32(node, key));
}

int16_t GetValue_Int16(const boost::property_tree::ptree& node, const std::string& key)
{
	return unsigned_to_signed(GetValue_UInt16(node, key));
}

int8_t GetValue_Int8(const boost::property_tree::ptree& node, const std::string& key)
{
	return unsigned_to_signed(GetValue_UInt8(node, key));
}

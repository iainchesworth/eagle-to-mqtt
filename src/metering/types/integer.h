#ifndef INTEGER_H
#define INTEGER_H

#include <boost/property_tree/ptree.hpp>

#include <functional>
#include <cstdint>
#include <string>

#include "metering/common/unit_converters.h"

uint64_t GetValue_UInt64(const boost::property_tree::ptree& node, const std::string& key, const std::function<uint64_t(const std::string& value)>& converter = [](const std::string& value) { return hex_string_to_uint64_t(value); });
uint32_t GetValue_UInt32(const boost::property_tree::ptree& node, const std::string& key, const std::function<uint32_t(const std::string& value)>& converter = [](const std::string& value) { return hex_string_to_uint32_t(value); });
uint16_t GetValue_UInt16(const boost::property_tree::ptree& node, const std::string& key, const std::function<uint16_t(const std::string& value)>& converter = [](const std::string& value) { return hex_string_to_uint16_t(value); });
uint8_t GetValue_UInt8(const boost::property_tree::ptree& node, const std::string& key, const std::function<uint8_t(const std::string& value)>& converter = [](const std::string& value) { return hex_string_to_uint8_t(value); });

int64_t GetValue_Int64(const boost::property_tree::ptree& node, const std::string& key);
int32_t GetValue_Int32(const boost::property_tree::ptree& node, const std::string& key);
int16_t GetValue_Int16(const boost::property_tree::ptree& node, const std::string& key);
int8_t GetValue_Int8(const boost::property_tree::ptree& node, const std::string& key);

#endif // INTEGER_H

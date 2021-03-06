#ifndef UNIT_CONVERTERS_H
#define UNIT_CONVERTERS_H

#include <chrono>
#include <cstdint>
#include <string>

uint64_t hex_string_to_uint64_t(const std::string& hex_string);
uint32_t hex_string_to_uint32_t(const std::string& hex_string);
uint16_t hex_string_to_uint16_t(const std::string& hex_string);
uint8_t hex_string_to_uint8_t(const std::string& hex_string);

int64_t unsigned_to_signed(uint64_t value);
int32_t unsigned_to_signed(uint32_t value);
int16_t unsigned_to_signed(uint16_t value);
int8_t unsigned_to_signed(uint8_t value);

std::chrono::time_point<std::chrono::system_clock> hex_string_to_timepoint(const std::string& hex_string);

#endif // UNIT_CONVERTERS_H

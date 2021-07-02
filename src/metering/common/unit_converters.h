#ifndef UNIT_CONVERTERS_H
#define UNIT_CONVERTERS_H

#include <cstdint>
#include <string>

#include "metering/common/timestamps.h"

uint64_t hex_string_to_uint64_t(const std::string& hex_string);
uint32_t hex_string_to_uint32_t(const std::string& hex_string);
uint16_t hex_string_to_uint16_t(const std::string& hex_string);
uint8_t hex_string_to_uint8_t(const std::string& hex_string);

int64_t unsigned_to_signed(uint64_t value);
int32_t unsigned_to_signed(uint32_t value);
int16_t unsigned_to_signed(uint16_t value);
int8_t unsigned_to_signed(uint8_t value);

timepoint_from_jan2000 hex_string_to_timepoint_since_jan2000(const std::string& hex_string);
timepoint_from_epoch hex_string_to_timepoint_since_epoch(const std::string& hex_string);

#endif // UNIT_CONVERTERS_H

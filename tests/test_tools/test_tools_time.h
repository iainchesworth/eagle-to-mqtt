#ifndef TEST_TOOLS_TIME_H
#define TEST_TOOLS_TIME_H

#include <chrono>
#include <iomanip>
#include <ostream>

namespace test_tools
{

auto within_60_seconds = [](const std::chrono::time_point<std::chrono::system_clock>& actual, const std::chrono::time_point<std::chrono::system_clock>& expected) -> bool
{
	auto fifty_nine_seconds = std::chrono::seconds(59);
	auto no_earlier_than = expected - fifty_nine_seconds;
	auto no_later_than = expected + fifty_nine_seconds;

	return ((no_earlier_than <= actual) && (no_later_than >= actual));
};

}
// namespace test_tools

#endif // TEST_TOOLS_TIME_H

#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <date/date.h>

#include <chrono>
#include <sstream>
#include <string>

using timepoint_from_jan2000 = std::chrono::time_point<std::chrono::system_clock>;
using timepoint_from_epoch = std::chrono::time_point<std::chrono::system_clock>;

namespace Timestamps
{
	template<typename TIMESTAMP_TYPE>
	std::string ToString(const TIMESTAMP_TYPE datetime)
	{
		using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

		std::chrono::time_point<std::chrono::system_clock> raw_datetime = datetime;

		std::ostringstream oss;
		oss << raw_datetime;

		return oss.str();
	}
}
// namespace Timestamps

#endif // TIMESTAMPS_H

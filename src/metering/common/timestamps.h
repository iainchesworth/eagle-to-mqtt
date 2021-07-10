#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <chrono>
#include <sstream>
#include <string>

using timepoint_from_jan2000 = std::chrono::time_point<std::chrono::system_clock>;
using timepoint_from_epoch = std::chrono::time_point<std::chrono::system_clock>;

std::ostream& operator<<(std::ostream& os, const std::chrono::time_point<std::chrono::system_clock>& tp);

namespace Timestamps
{
	template<typename TIMESTAMP_TYPE>
	std::string ToString(const TIMESTAMP_TYPE datetime)
	{
		std::ostringstream oss;
		oss << datetime;

		return oss.str();
	}
}
// namespace Timestamps

#endif // TIMESTAMPS_H

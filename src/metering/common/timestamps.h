#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <chrono>
#include <string>

using timepoint_from_jan2000 = std::chrono::time_point<std::chrono::system_clock>;
using timepoint_from_epoch = std::chrono::time_point<std::chrono::system_clock>;

namespace Timestamps
{
	std::string ToString(const timepoint_from_jan2000& datetime);
}
// namespace Timestamps

#endif // TIMESTAMPS_H

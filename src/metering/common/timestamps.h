#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <chrono>

using timepoint_from_jan2000 = std::chrono::time_point<std::chrono::system_clock>;
using timepoint_from_epoch = std::chrono::time_point<std::chrono::system_clock>;

#endif // TIMESTAMPS_H

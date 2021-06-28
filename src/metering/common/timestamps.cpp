#include <date/date.h>

#include <sstream>

#include "timestamps.h"

using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

std::string Timestamps::ToString(const timepoint_from_jan2000& datetime)
{
	std::chrono::time_point<std::chrono::system_clock> raw_datetime = datetime;

	std::ostringstream oss;
	oss << raw_datetime;

	return oss.str();
}

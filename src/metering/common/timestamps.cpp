#include <date/date.h>

#include "metering/common/timestamps.h"

std::ostream& operator<<(std::ostream& os, const std::chrono::time_point<std::chrono::system_clock>& tp)
{
	// Leverage Howard Hinnant's date library to get the iostream support.
	date::operator<<(os, tp);

	return os;
}

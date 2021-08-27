#include <date/date.h>

#include <sstream>

#include "metering/common/timestamps.h"
#include "metering/common/unit_converters.h"

UnixTimepoint::UnixTimepoint() :
	UnixTimepoint(std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(0)))
{
}

UnixTimepoint::UnixTimepoint(const std::string& unix_timepoint) :
	UnixTimepoint(FromHexString(unix_timepoint))
{
}

UnixTimepoint::UnixTimepoint(const std::chrono::time_point<std::chrono::system_clock>& unix_timepoint) :
	m_Timepoint(unix_timepoint)
{
}

UnixTimepoint UnixTimepoint::FromHexString(const std::string& unix_timepoint_string)
{
	return UnixTimepoint(hex_string_to_timepoint(unix_timepoint_string));
}

UnixTimepoint UnixTimepoint::FromRFC3339String(const std::string& unix_timepoint_string)
{
	std::istringstream iss{ unix_timepoint_string };
	date::sys_seconds tp;

	iss >> date::parse("%FT%T%Ez", tp);

	return UnixTimepoint(tp);
}

std::string UnixTimepoint::ToString(const UnixTimepoint& unix_timepoint)
{
	std::ostringstream oss;

	date::operator<<(oss, unix_timepoint.m_Timepoint);

	return oss.str();
}

bool UnixTimepoint::operator==(const UnixTimepoint& rhs) const
{
	return std::chrono::operator==(m_Timepoint, rhs.m_Timepoint);
}

UnixTimepoint& UnixTimepoint::operator=(const std::chrono::time_point<std::chrono::system_clock>& rhs)
{
	m_Timepoint = rhs;
	return *this;
}

bool operator<(const UnixTimepoint& lhs, const UnixTimepoint& rhs)
{
	return (lhs.m_Timepoint < rhs.m_Timepoint);
}

std::ostream& operator<<(std::ostream& os, const UnixTimepoint& unix_timepoint)
{
	date::operator<<(os, unix_timepoint.m_Timepoint);
	return os;
}

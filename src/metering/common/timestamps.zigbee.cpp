#include <date/date.h>

#include <sstream>

#include "metering/common/timestamps.h"
#include "metering/common/unit_converters.h"

ZigbeeTimepoint::ZigbeeTimepoint() :
	ZigbeeTimepoint(std::chrono::time_point<std::chrono::system_clock>(std::chrono::seconds(0)))
{
}

ZigbeeTimepoint::ZigbeeTimepoint(const std::string& zigbee_timepoint) :
	ZigbeeTimepoint(FromString(zigbee_timepoint))
{
}

ZigbeeTimepoint::ZigbeeTimepoint(const std::chrono::time_point<std::chrono::system_clock>& zigbee_timepoint) :
	m_Timepoint(zigbee_timepoint)
{
}

ZigbeeTimepoint ZigbeeTimepoint::FromString(const std::string& zigbee_timepoint_string)
{
	std::chrono::time_point<std::chrono::system_clock> timepoint_without_offset = hex_string_to_timepoint(zigbee_timepoint_string);
	
	auto timepoint_with_offset = timepoint_without_offset + DIFFERENCE_IN_SECONDS_FROM_1970_TO_2000;

	return ZigbeeTimepoint(timepoint_with_offset);
}

std::string ZigbeeTimepoint::ToString(const ZigbeeTimepoint& zigbee_timepoint)
{
	std::ostringstream oss;

	date::operator<<(oss, zigbee_timepoint.m_Timepoint);

	return oss.str();
}

bool ZigbeeTimepoint::operator==(const ZigbeeTimepoint& rhs) const
{
	return std::chrono::operator==(m_Timepoint, rhs.m_Timepoint);
}

bool operator<(const ZigbeeTimepoint& lhs, const ZigbeeTimepoint& rhs)
{
	return (lhs.m_Timepoint < rhs.m_Timepoint);
}

std::ostream& operator<<(std::ostream& os, const ZigbeeTimepoint& zigbee_timepoint)
{
	date::operator<<(os, zigbee_timepoint.m_Timepoint);
	return os;
}

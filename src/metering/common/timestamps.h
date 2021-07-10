#ifndef TIMESTAMPS_H
#define TIMESTAMPS_H

#include <chrono>
#include <ostream>
#include <string>

class ZigbeeTimepoint
{
	static constexpr std::chrono::seconds DIFFERENCE_IN_SECONDS_FROM_1970_TO_2000{ 946684800 };

public:
	ZigbeeTimepoint(const std::string& timepoint);
	virtual ~ZigbeeTimepoint();

private:
	ZigbeeTimepoint();
	ZigbeeTimepoint(const std::chrono::time_point<std::chrono::system_clock>& zigbee_timepoint);

public:
	static ZigbeeTimepoint FromString(const std::string& zigbee_timepoint_string);
	static std::string ToString(const ZigbeeTimepoint zigbee_timepoint);

public:
	bool operator==(const ZigbeeTimepoint& rhs) const;

private:
	std::chrono::time_point<std::chrono::system_clock> m_Timepoint;

private:
	friend bool operator<(const ZigbeeTimepoint& lhs, const ZigbeeTimepoint& rhs);
	friend std::ostream& operator<<(std::ostream& os, const ZigbeeTimepoint& zigbee_timepoint);
};

//---------------------------------------------------------------------------------------------------------------------
//
//
// 
//---------------------------------------------------------------------------------------------------------------------

class UnixTimepoint
{
public:
	UnixTimepoint();
	UnixTimepoint(const std::string& unix_timepoint);
	virtual ~UnixTimepoint();

private:
	UnixTimepoint(const std::chrono::time_point<std::chrono::system_clock>& unix_timepoint);

public:
	static UnixTimepoint FromString(const std::string& unix_timepoint_string);
	static std::string ToString(const UnixTimepoint unix_timepoint);

public:
	bool operator==(const UnixTimepoint& rhs) const;

public:
	UnixTimepoint& operator=(const std::chrono::time_point<std::chrono::system_clock>& rhs);

public:
	template<typename DURATION_TYPE>
	UnixTimepoint& operator+=(const std::chrono::duration<DURATION_TYPE>& rhs)
	{
		m_Timepoint += rhs;
		return *this;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_Timepoint;

private:
	friend bool operator<(const UnixTimepoint& lhs, const UnixTimepoint& rhs);
	friend std::ostream& operator<<(std::ostream& os, const UnixTimepoint& unix_timepoint);
};

#endif // TIMESTAMPS_H

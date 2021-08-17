#ifndef METER_LOCATIONS_H
#define METER_LOCATIONS_H

#include <ostream>
#include <string>

class MeterLocations
{
	static const std::string NOT_SPECIFIED;
	static const std::string LOAD;
	static const std::string GRID;
	static const std::string UNKNOWN;

public:
	enum class Locations
	{
		NotSpecified,
		Load,
		Grid,
		Unknown
	};

public:
	MeterLocations();
	explicit MeterLocations(Locations location);
	explicit MeterLocations(const std::string& location);

private:
	Locations m_Location;

public:
	static Locations FromString(const std::string& location_string);
	static std::string ToString(const Locations location_type);

public:
	bool operator==(const MeterLocations& meter_location) const;
	bool operator==(const Locations& location) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const MeterLocations& meter_location);
};

#endif // METER_LOCATIONS_H

#ifndef UNITS_OF_MEASURE_H
#define UNITS_OF_MEASURE_H

#include <ostream>
#include <string>

class UnitsOfMeasure
{
	static const std::string NOT_SPECIFIED;
	static const std::string WATTS;
	static const std::string KILOWATTS;
	static const std::string WATT_HOURS;
	static const std::string KILOWATT_HOURS;
	static const std::string UNKNOWN;

public:
	enum class Units
	{
		NotSpecified,

		Watts,
		Kilowatts,

		WattHours,
		KilowattHours,

		Unknown
	};

public:
	UnitsOfMeasure();
	explicit UnitsOfMeasure(Units units);
	explicit UnitsOfMeasure(const std::string& units);

private:
	Units m_Units;

public:
	static Units FromString(const std::string& units_string);
	static std::string ToString(const Units units);

public:
	Units operator()() const;
	bool operator==(const UnitsOfMeasure& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const UnitsOfMeasure& units);
};


#endif // UNITS_OF_MEASURE_H

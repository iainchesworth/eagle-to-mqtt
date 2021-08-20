#ifndef PERCENTAGE_H
#define PERCENTAGE_H

#include <cstdint>
#include <ostream>
#include <string>

class Percentage
{
public:
	using value_type = long double;

public:
	explicit Percentage(float percentage);
	explicit Percentage(double percentage);
	explicit Percentage(uint8_t percentage);
	explicit Percentage(uint16_t percentage);
	explicit Percentage(uint32_t percentage);
	explicit Percentage(uint64_t percentage);

public:
	explicit Percentage(long double percentage, uint8_t decimal_places = 2);

private:
	void ValidateAndStorePercentage(const value_type percentage);

public:
	value_type operator()() const;

private:
	value_type m_Percentage;
	uint32_t m_DecimalPlacesToShow;

public:
	bool operator==(const float other) const;
	bool operator==(const double other) const;
	bool operator==(const long double other) const;
	bool operator==(const uint8_t other) const;
	bool operator==(const uint16_t other) const;
	bool operator==(const uint32_t other) const;
	bool operator==(const uint64_t other) const;
	bool operator==(const Percentage& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const Percentage& percentage);
};

#endif // PERCENTAGE_H

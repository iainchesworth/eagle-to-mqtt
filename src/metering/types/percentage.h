#ifndef PERCENTAGE_H
#define PERCENTAGE_H

#include <cstdint>
#include <ostream>

class Percentage
{
public:
	explicit Percentage(float percentage);
	explicit Percentage(double percentage);
	explicit Percentage(uint8_t percentage);
	explicit Percentage(uint16_t percentage);
	explicit Percentage(uint32_t percentage);
	explicit Percentage(uint64_t percentage);

private:
	void ValidateAndStorePercentage(double percentage);

public:
	double operator()() const;

private:
	double m_Percentage;

public:
	friend std::ostream& operator<<(std::ostream& os, const Percentage& percentage);
};

#endif // PERCENTAGE_H

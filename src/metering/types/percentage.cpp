#include <spdlog/spdlog.h>

#include <cmath>
#include <iomanip>

#include "metering/types/percentage.h"

Percentage::Percentage(float percentage)
{
	ValidateAndStorePercentage(static_cast<double>(percentage));
}

Percentage::Percentage(double percentage)
{
	ValidateAndStorePercentage(percentage);
}

Percentage::Percentage(uint8_t percentage)
{
	ValidateAndStorePercentage(static_cast<double>(percentage));
}

Percentage::Percentage(uint16_t percentage)
{
	ValidateAndStorePercentage(static_cast<double>(percentage));
}

Percentage::Percentage(uint32_t percentage)
{
	ValidateAndStorePercentage(static_cast<double>(percentage));
}

Percentage::Percentage(uint64_t percentage)
{
	ValidateAndStorePercentage(static_cast<double>(percentage));
}

void Percentage::ValidateAndStorePercentage(double percentage)
{
	static const double MINIMUM = 0.0f;
	static const double MAXIMUM = 100.0f;

	if (std::isnan(percentage) || std::isinf(percentage))
	{
		static const std::string error_message{ "Percentage()::ValidateAndStorePercentage - not a percentage; floating point value was NaN or Infinite" };

		spdlog::debug(error_message);
		throw std::invalid_argument(error_message);
	}
	else if (std::isgreater(percentage, MAXIMUM))
	{
		static const std::string error_message{ "Percentage()::ValidateAndStorePercentage - not a percentage; value exceeded 100.0%" };

		spdlog::debug(error_message);
		throw std::out_of_range(error_message);
	}
	else if (std::isless(percentage, MINIMUM))
	{
		static const std::string error_message{ "Percentage()::ValidateAndStorePercentage - not a percentage; value was less than 0.0%" };

		spdlog::debug(error_message);
		throw std::out_of_range(error_message);
	}
	else
	{
		// Everything is good...save the percentage.
		m_Percentage = percentage;
	}
}

double Percentage::operator()() const
{
	return m_Percentage;
}

std::ostream& operator<<(std::ostream& os, const Percentage& percentage)
{
	os << std::fixed << std::setprecision(2) << percentage.m_Percentage << "%";
	return os;
}

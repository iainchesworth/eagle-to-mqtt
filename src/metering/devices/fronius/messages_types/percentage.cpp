#include <spdlog/spdlog.h>

#include <cmath>
#include <iomanip>
#include <limits>

#include "metering/devices/fronius/messages_types/percentage.h"

Percentage::Percentage(float percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(double percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(uint8_t percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(uint16_t percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(uint32_t percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(uint64_t percentage) :
	Percentage(static_cast<value_type>(percentage))
{
}

Percentage::Percentage(long double percentage, uint8_t decimal_places) :
	m_DecimalPlacesToShow(decimal_places)
{
	ValidateAndStorePercentage(percentage);
}

void Percentage::ValidateAndStorePercentage(const value_type percentage)
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

Percentage::value_type Percentage::operator()() const
{
	return m_Percentage;
}

bool Percentage::operator==(const float other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const double other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const long double other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const uint8_t other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const uint16_t other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const uint32_t other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const uint64_t other) const
{
	return (*this == Percentage(other));
}

bool Percentage::operator==(const Percentage& other) const
{
	return std::fabs(m_Percentage - other.m_Percentage) < std::numeric_limits<value_type>::epsilon();
}

std::ostream& operator<<(std::ostream& os, const Percentage& percentage)
{
	os << std::fixed << std::setprecision(percentage.m_DecimalPlacesToShow) << percentage.m_Percentage << "%";
	return os;
}

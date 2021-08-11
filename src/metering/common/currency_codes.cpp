#include <spdlog/spdlog.h>

#include "exceptions/invalid_currency_value.h"
#include "metering/common/currency_codes.h"
#include "metering/common/unit_converters.h"

const std::string CurrencyCodes::NOT_SPECIFIED{ "Not Specified" };
const std::string CurrencyCodes::AUD{ "AUD" };
const std::string CurrencyCodes::USD{ "USD" };
const std::string CurrencyCodes::XXX{ "XXX" };
const std::string CurrencyCodes::UNKNOWN{ "Unknown" };

CurrencyCodes::CurrencyCodes() :
	CurrencyCodes(ISO4127_CurrencyCodes::NotSpecified)
{
}

CurrencyCodes::CurrencyCodes(ISO4127_CurrencyCodes currency_code) :
	m_CurrencyCode(currency_code)
{
}

CurrencyCodes::CurrencyCodes(const std::string& currency_code) :
	m_CurrencyCode(FromString(currency_code))
{
}

CurrencyCodes::ISO4127_CurrencyCodes CurrencyCodes::FromString(const std::string& currency_code_string)
{
	ISO4127_CurrencyCodes currency_code;

	if (6 != currency_code_string.length()) // Format is 0x1234
	{
		spdlog::warn("Unknown string value provided for currency code");
		throw InvalidCurrencyValue("Currency value has invalid length - expected 6, got " + std::to_string(currency_code_string.length()));
	}
	else
	{
		const auto currency_as_int = hex_string_to_uint16_t(currency_code_string);
		switch (currency_as_int) // Cannot cast as casting from a non-valid enum <value> is UD
		{
		case 36: currency_code = ISO4127_CurrencyCodes::AUD; break;
		case 840: currency_code = ISO4127_CurrencyCodes::USD; break;
		case 999: currency_code = ISO4127_CurrencyCodes::XXX; break;

		default:
			spdlog::warn("Unknown currency code provided to converter: {}", currency_code_string);
			currency_code = ISO4127_CurrencyCodes::Unknown;
			break;
		}
	}

	return currency_code;
}

std::string CurrencyCodes::ToString(const ISO4127_CurrencyCodes currency_code)
{
	switch (currency_code)
	{
	case ISO4127_CurrencyCodes::NotSpecified:
		return NOT_SPECIFIED;
	case ISO4127_CurrencyCodes::AUD:
		return AUD;
	case ISO4127_CurrencyCodes::USD:
		return USD;
	case ISO4127_CurrencyCodes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool CurrencyCodes::operator==(const CurrencyCodes& other) const
{
	return (m_CurrencyCode == other.m_CurrencyCode);
}

bool CurrencyCodes::operator==(const ISO4127_CurrencyCodes& currency_code) const
{
	return (m_CurrencyCode == currency_code);
}

std::ostream& operator<<(std::ostream& os, const CurrencyCodes& currency_code)
{
	os << currency_code.ToString(currency_code.m_CurrencyCode);
	return os;
}

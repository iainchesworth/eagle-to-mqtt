#ifndef CURRENCY_CODES_H
#define CURRENCY_CODES_H

#include <boost/optional.hpp>

#include <ostream>
#include <string>

class CurrencyCodes
{
	static const std::string NOT_SPECIFIED;
	static const std::string AUD;
	static const std::string USD;
	static const std::string XXX;
	static const std::string UNKNOWN;

public:
	enum class ISO4127_CurrencyCodes
	{
		NotSpecified = 0,	// Note that '000-008' are not active currency codes
		AUD = 36,
		USD = 840,
		XXX = 999,
		Unknown = 1000		// Note that all currency codes are three-digits so 1000 is unused
	};

public:
	struct PropertyTreeTranslator
	{
		using external_type = CurrencyCodes;
		using internal_type = std::string;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

public:
	CurrencyCodes();
	explicit CurrencyCodes(ISO4127_CurrencyCodes currency_code);
	explicit CurrencyCodes(const std::string& currency_code);

private:
	ISO4127_CurrencyCodes m_CurrencyCode;

public:
	static ISO4127_CurrencyCodes FromString(const std::string& currency_code_string);
	static std::string ToString(const ISO4127_CurrencyCodes currency_code);

public:
	bool operator==(const CurrencyCodes& other) const;
	bool operator==(const ISO4127_CurrencyCodes& currency_code) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const CurrencyCodes& currency_code);
};

#endif // CURRENCY_CODES_H

#ifndef CURRENCY_CODES_H
#define CURRENCY_CODES_H

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
		NotSpecified,
		AUD = 36,
		USD = 840,
		XXX = 999,
		Unknown
	};

public:
	CurrencyCodes();
	CurrencyCodes(ISO4127_CurrencyCodes currency_code);
	CurrencyCodes(const std::string& currency_code);

private:
	ISO4127_CurrencyCodes m_CurrencyCode;

public:
	static ISO4127_CurrencyCodes FromString(const std::string& currency_code_string);
	static std::string ToString(const ISO4127_CurrencyCodes currency_code);

public:
	bool operator==(const CurrencyCodes& other) const;

public:
	friend std::ostream& operator<<(std::ostream& os, const CurrencyCodes& currency_code);
};

#endif // CURRENCY_CODES_H

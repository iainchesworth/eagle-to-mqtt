#include "metering/fragment_processors/partial_fragment_types/pricing_info.h"
#include "metering/type_handlers/essential.h"
#include "metering/type_handlers/integer.h"
#include "metering/type_handlers/optional.h"

PricingInfo::PricingInfo(CurrencyCodes currency, double price) :
	m_Currency(currency),
	m_Price(price)
{
}

CurrencyCodes PricingInfo::Currency() const
{
	return m_Currency;
}

double PricingInfo::Price() const
{
	return m_Price;
}

PricingInfo PricingInfo::ExtractFromPayload(const boost::property_tree::ptree& node)
{
	auto currency_code = IsOptionalWithDefault<CurrencyCodes>(node, "Currency", CurrencyCodes::ISO4127_CurrencyCodes::NotSpecified);
	auto price_as_double = static_cast<double>(IsEssential<uint64_t>(node, "Price"));
	auto trailing_digits = IsEssential<uint8_t>(node, "TrailingDigits");

	for (int i = 0; i < trailing_digits; ++i)
	{
		price_as_double /= 10;
	}

	return PricingInfo(currency_code, price_as_double);
}

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
	struct CurrencyCodes_PropertyTreeTranslator
	{
		typedef CurrencyCodes external_type;
		typedef std::string internal_type;

		boost::optional<external_type> get_value(const internal_type& value)
		{
			return external_type(value);
		}
	};

	auto currency_code = IsOptional<CurrencyCodes>([&node]() -> CurrencyCodes { return node.get<CurrencyCodes>("Currency", CurrencyCodes_PropertyTreeTranslator()); });
	auto price_as_double = IsEssential<double>([&node]() -> double { return static_cast<double>(GetValue_Int32(node, "Price")); });
	auto trailing_digits = IsEssential<uint8_t>([&node]() -> uint8_t { return GetValue_UInt8(node, "TrailingDigits"); });

	for (int i = 0; i < trailing_digits; ++i)
	{
		price_as_double /= 10;
	}

	return PricingInfo(currency_code, price_as_double);
}

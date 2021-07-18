#ifndef PRICING_INFO
#define PRICING_INFO

#include <boost/property_tree/ptree.hpp>

#include "metering/common/currency_codes.h"

class PricingInfo
{
public:
	PricingInfo(CurrencyCodes currency, double price);

public:
	CurrencyCodes Currency() const;
	double Price() const;

private:
	CurrencyCodes m_Currency;
	double m_Price;

public:
	static PricingInfo ExtractFromPayload(const boost::property_tree::ptree& node);
};

#endif // PRICING INFO

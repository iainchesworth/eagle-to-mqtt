#ifndef BLOCK_PRICE_DETAIL_H
#define BLOCK_PRICE_DETAIL_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/currency_codes.h"
#include "metering/fragment_processors/partial_fragment_types/block_period.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class BlockPriceDetail : public IFragmentProcessor
{
public:
	BlockPriceDetail(const boost::property_tree::ptree& node);
	virtual ~BlockPriceDetail();

public:
	BlockPeriod CurrentBlock() const;

private:
	ZigBeeMacId m_MeterMacId;
	timepoint_from_jan2000 m_Timestamp;
	BlockPeriod m_CurrentBlock;
	CurrencyCodes m_Currency;
};

#endif // BLOCK_PRICE_DETAIL_H

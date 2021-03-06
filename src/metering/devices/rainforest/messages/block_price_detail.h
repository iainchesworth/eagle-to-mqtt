#ifndef BLOCK_PRICE_DETAIL_H
#define BLOCK_PRICE_DETAIL_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/currency_codes.h"
#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/messages/partial_message_types/block_period.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class BlockPriceDetail : public IFragmentProcessor
{
	static const std::string FIELDNAME_METERMACID;
	static const std::string FIELDNAME_TIMESTAMP;
	static const std::string FIELDNAME_CURRENCY;

public:
	explicit BlockPriceDetail(const boost::property_tree::ptree& node);
	virtual ~BlockPriceDetail() = default;

public:
	BlockPeriod CurrentBlock() const;

private:
	std::optional<ZigBeeMacId> m_MeterMacId;
	std::optional<ZigbeeTimepoint> m_Timestamp;
	BlockPeriod m_CurrentBlock;
	CurrencyCodes m_Currency;
};

#endif // BLOCK_PRICE_DETAIL_H

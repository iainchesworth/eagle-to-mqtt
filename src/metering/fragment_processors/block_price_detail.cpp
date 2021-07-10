#include "metering/fragment_processors/block_price_detail.h"
#include "metering/type_handlers/optional.h"

const std::string BlockPriceDetail::FIELDNAME_METERMACID{ "MeterMacId" };
const std::string BlockPriceDetail::FIELDNAME_TIMESTAMP{ "TimeStamp" };
const std::string BlockPriceDetail::FIELDNAME_CURRENCY{ "Currency" };

BlockPriceDetail::BlockPriceDetail(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsOptional<ZigBeeMacId>(node, FIELDNAME_METERMACID)),
	m_Timestamp(IsOptional<ZigbeeTimepoint>(node, FIELDNAME_TIMESTAMP)),
	m_CurrentBlock(BlockPeriod::ExtractFromPayload(node)),
	m_Currency(IsOptionalWithDefault<CurrencyCodes>(node, FIELDNAME_CURRENCY, CurrencyCodes::ISO4127_CurrencyCodes::NotSpecified))
{
}

BlockPriceDetail::~BlockPriceDetail()
{
}

BlockPeriod BlockPriceDetail::CurrentBlock() const
{
	return m_CurrentBlock;
}

#include "metering/fragment_processors/block_price_detail.h"
#include "metering/type_handlers/expected.h"
#include "metering/type_handlers/optional.h"

BlockPriceDetail::BlockPriceDetail(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_MeterMacId(IsExpected<ZigBeeMacId>([&node]() -> ZigBeeMacId { return ZigBeeMacId::ExtractFromPayload(node, "MeterMacId"); })),
	m_Timestamp(hex_string_to_timepoint_since_jan2000(node.get<std::string>("TimeStamp"))),
	m_CurrentBlock(BlockPeriod::ExtractFromPayload(node)),
	m_Currency(IsOptional<CurrencyCodes>([&node]() -> CurrencyCodes { return node.get<CurrencyCodes>("Currency", CurrencyCodes::PropertyTreeTranslator()); }))
{
}

BlockPriceDetail::~BlockPriceDetail()
{
}

BlockPeriod BlockPriceDetail::CurrentBlock() const
{
	return m_CurrentBlock;
}

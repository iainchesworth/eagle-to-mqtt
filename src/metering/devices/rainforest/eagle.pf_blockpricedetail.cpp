#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const BlockPriceDetail& block_price_detail)
{
	spdlog::trace("ProcessFragment(BlockPriceDetail) - not handled");
}

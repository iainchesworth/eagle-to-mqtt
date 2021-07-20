#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const BlockPriceDetail& block_price_detail)
{
	BOOST_LOG_TRIVIAL(trace) << L"ProcessFragment(BlockPriceDetail) - not handled";
}

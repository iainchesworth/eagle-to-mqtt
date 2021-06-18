#ifndef FRAGMENT_TYPES_H
#define FRAGMENT_TYPES_H

#include <string_view>

enum class FragmentTypes
{
	BillingPeriodList,
	BlockPriceDetail,
	ConnectionStatus,
	CurrentSummation,
	DeviceInfo,
	InstantaneousDemand,
	MessageCluster,
	NetworkInfo,
	PriceCluster,
	TimeCluster
};

FragmentTypes string_view_to_fragmenttype(const std::string_view& fragment);

#endif // FRAGMENT_TYPES_H

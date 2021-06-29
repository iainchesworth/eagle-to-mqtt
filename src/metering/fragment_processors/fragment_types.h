#ifndef FRAGMENT_TYPES_H
#define FRAGMENT_TYPES_H

#include <string>

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

FragmentTypes string_view_to_fragmenttype(const std::string& fragment);

#endif // FRAGMENT_TYPES_H

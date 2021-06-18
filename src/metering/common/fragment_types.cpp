#include <boost/log/trivial.hpp>

#include "exceptions/unknown_fragment_type.h"
#include "metering/common/fragment_types.h"

FragmentTypes string_view_to_fragmenttype(const std::string_view& fragment)
{
	if (0 == fragment.compare("BillingPeriodList")) return FragmentTypes::BillingPeriodList;
	if (0 == fragment.compare("BlockPriceDetail")) return FragmentTypes::BlockPriceDetail;
	if (0 == fragment.compare("ConnectionStatus")) return FragmentTypes::ConnectionStatus;
	if (0 == fragment.compare("CurrentSummation")) return FragmentTypes::CurrentSummation;
	if (0 == fragment.compare("DeviceInfo")) return FragmentTypes::DeviceInfo;
	if (0 == fragment.compare("InstantaneousDemand")) return FragmentTypes::InstantaneousDemand;
	if (0 == fragment.compare("MessageCluster")) return FragmentTypes::MessageCluster;
	if (0 == fragment.compare("NetworkInfo")) return FragmentTypes::NetworkInfo;
	if (0 == fragment.compare("PriceCluster")) return FragmentTypes::PriceCluster;
	if (0 == fragment.compare("TimeCluster")) return FragmentTypes::TimeCluster;

	throw UnknownFragmentType(fragment);
}

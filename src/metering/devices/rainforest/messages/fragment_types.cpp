#include <spdlog/spdlog.h>

#include "exceptions/unknown_fragment_type.h"
#include "metering/devices/rainforest/messages/fragment_types.h"

const std::string Fragments::NOT_SPECIFIED{ "Not Specified" };
const std::string Fragments::BILLING_PERIOD_LIST{ "BillingPeriodList" };
const std::string Fragments::BLOCK_PRICE_DETAIL{ "BlockPriceDetail" };
const std::string Fragments::CONNECTION_STATUS{ "ConnectionStatus" };
const std::string Fragments::CURRENT_SUMMATION{ "CurrentSummation" };
const std::string Fragments::CURRENT_SUMMATION_DELIVERED{ "CurrentSummationDelivered" };
const std::string Fragments::DEVICE_INFO{ "DeviceInfo" };
const std::string Fragments::INSTANTANEOUS_DEMAND{ "InstantaneousDemand" };
const std::string Fragments::MESSAGE_CLUSTER{ "MessageCluster" };
const std::string Fragments::NETWORK_INFO{ "NetworkInfo" };
const std::string Fragments::PRICE_CLUSTER{ "PriceCluster" };
const std::string Fragments::TIME_CLUSTER{ "TimeCluster" };
const std::string Fragments::UNKNOWN{ "Unknown" };

Fragments::Fragments() :
	Fragments(FragmentTypes::NotSpecified)
{
}

Fragments::Fragments(FragmentTypes fragment) :
	m_Fragment(fragment)
{
}

Fragments::Fragments(const std::string& fragment) :
	m_Fragment(FromString(fragment))
{
}

Fragments::FragmentTypes Fragments::FromString(const std::string& fragment_string)
{
	FragmentTypes fragment_type = FragmentTypes::NotSpecified;

	if (0 == fragment_string.length())
	{
		spdlog::warn("Invalid FragmentType provided to converter (zero-length)");
		throw UnknownFragmentType("Zero-length fragment type value");
	}
	else if (BILLING_PERIOD_LIST == fragment_string)
	{
		fragment_type = FragmentTypes::BillingPeriodList;
	}
	else if (BLOCK_PRICE_DETAIL == fragment_string)
	{
		fragment_type = FragmentTypes::BlockPriceDetail;
	}
	else if (CONNECTION_STATUS == fragment_string)
	{
		fragment_type = FragmentTypes::ConnectionStatus;
	}
	else if (CURRENT_SUMMATION == fragment_string)
	{
		fragment_type = FragmentTypes::CurrentSummation;
	}
	else if (CURRENT_SUMMATION_DELIVERED == fragment_string)
	{
		fragment_type = FragmentTypes::CurrentSummation;
	}
	else if (DEVICE_INFO == fragment_string)
	{
		fragment_type = FragmentTypes::DeviceInfo;
	}
	else if (INSTANTANEOUS_DEMAND == fragment_string)
	{
		fragment_type = FragmentTypes::InstantaneousDemand;
	}
	else if (MESSAGE_CLUSTER == fragment_string)
	{
		fragment_type = FragmentTypes::MessageCluster;
	}
	else if (NETWORK_INFO == fragment_string)
	{
		fragment_type = FragmentTypes::NetworkInfo;
	}
	else if (PRICE_CLUSTER == fragment_string)
	{
		fragment_type = FragmentTypes::PriceCluster;
	}
	else if (TIME_CLUSTER == fragment_string)
	{
		fragment_type = FragmentTypes::TimeCluster;
	}
	else
	{
		spdlog::warn("Unknown Fragment Type provided to converter: {}", fragment_string);
		fragment_type = FragmentTypes::Unknown;
	}

	return fragment_type;
}

std::string Fragments::ToString(const FragmentTypes fragment_type)
{
	switch (fragment_type)
	{
	case FragmentTypes::NotSpecified:
		return NOT_SPECIFIED;
	case FragmentTypes::BillingPeriodList:
		return BILLING_PERIOD_LIST;
	case FragmentTypes::BlockPriceDetail:
		return BLOCK_PRICE_DETAIL;
	case FragmentTypes::ConnectionStatus:
		return CONNECTION_STATUS;
	case FragmentTypes::CurrentSummation:
		return CURRENT_SUMMATION;
	case FragmentTypes::DeviceInfo:
		return DEVICE_INFO;
	case FragmentTypes::InstantaneousDemand:
		return INSTANTANEOUS_DEMAND;
	case FragmentTypes::MessageCluster:
		return MESSAGE_CLUSTER;
	case FragmentTypes::NetworkInfo:
		return NETWORK_INFO;
	case FragmentTypes::PriceCluster:
		return PRICE_CLUSTER;
	case FragmentTypes::TimeCluster:
		return TIME_CLUSTER;
	case FragmentTypes::Unknown:
	default:
		return UNKNOWN;
	}
}

bool Fragments::operator==(const Fragments& other) const
{
	return (m_Fragment == other.m_Fragment);
}

bool Fragments::operator==(const FragmentTypes& fragment_type) const
{
	return (m_Fragment == fragment_type);
}

std::ostream& operator<<(std::ostream& os, const Fragments& fragment)
{
	os << Fragments::ToString(fragment.m_Fragment);
	return os;
}

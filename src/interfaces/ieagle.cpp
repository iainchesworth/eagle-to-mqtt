#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>

#include <string_view>

#include "interfaces/ieagle.h"
#include "metering/common/ethernet_mac_id.h"
#include "metering/common/fragment_types.h"

IEagle::IEagle() :
	m_DeviceMacId(),
	m_DemandHistory()
{
}

void IEagle::ProcessFragment(const ConnectionStatus& connection_status)
{
}

void IEagle::ProcessFragment(const CurrentSummation& current_summation)
{
}

void IEagle::ProcessFragment(const DeviceInfo& device_info)
{
}

void IEagle::ProcessFragment(const InstantaneousDemand& instantaneous_demand)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing instantaneous demand history element (" << instantaneous_demand.Demand().Demand() << L")";
	m_DemandHistory.insert(std::make_pair(instantaneous_demand.Timestamp(), instantaneous_demand.Demand()));
}

void IEagle::ProcessFragment(const NetworkInfo& network_info)
{
}

void IEagle::ProcessPayload(const boost::property_tree::ptree& node)
{
	BOOST_FOREACH(const boost::property_tree::ptree::value_type & v, node.get_child("rainforest"))
	{
		// v.first is the name of the child.
		// v.second is the child tree.

		const std::string_view node_name = v.first;
		const boost::property_tree::ptree node_data = v.second;

		if (0 == v.first.compare("<xmlattr>"))
		{
			// Capture the timestamp for this device payload
			
			// Capture the device mac id.
			const auto mac_id = node_data.get_optional<std::string>("macId");
			if (mac_id.is_initialized())
			{
				m_DeviceMacId = EthernetMacId(mac_id.get());
			}
		}
		else
		{
			switch (string_view_to_fragmenttype(node_name))
			{
			case FragmentTypes::ConnectionStatus:
				BOOST_LOG_TRIVIAL(debug) << L"Processing ConnectionStatus fragment";
				ProcessFragment(ConnectionStatus(node_data));
				break;

			case FragmentTypes::CurrentSummation:
				BOOST_LOG_TRIVIAL(debug) << L"Processing CurrentSummation fragment";
				ProcessFragment(CurrentSummation(node_data));
				break;

			case FragmentTypes::DeviceInfo:
				BOOST_LOG_TRIVIAL(debug) << L"Processing DeviceInfo fragment";
				ProcessFragment(DeviceInfo(node_data));
				break;

			case FragmentTypes::InstantaneousDemand:
				BOOST_LOG_TRIVIAL(debug) << L"Processing InstantaneousDemand fragment";
				ProcessFragment(InstantaneousDemand(node_data));
				break;

			case FragmentTypes::NetworkInfo:
				BOOST_LOG_TRIVIAL(debug) << L"Processing NetworkInfo fragment";
				ProcessFragment(NetworkInfo(node_data));
				break;

			case FragmentTypes::BillingPeriodList:
			case FragmentTypes::BlockPriceDetail:
			case FragmentTypes::MessageCluster:
			case FragmentTypes::PriceCluster:
			case FragmentTypes::TimeCluster:
			default:
				BOOST_LOG_TRIVIAL(debug) << L"Ignoring unhandled XML fragments in upload data set";
				break;
			}
		}
	}
}

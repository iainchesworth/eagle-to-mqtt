#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>

#include <stdexcept>
#include <string_view>

#include "exceptions/unknown_fragment_type.h"
#include "interfaces/ieagle.h"
#include "metering/fragment_processors/fragment_types.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"

IEagle::IEagle() :
	m_LastMessageTimestamp(),
	m_EthernetMacId(),
	m_ZigbeeMacId(),
	m_CoordinatorZigbeeMacId(),
	m_DemandHistory()
{
}

void IEagle::ProcessPayload(const boost::property_tree::ptree& node)
{
	try
	{
		const auto rainforest_node = node.get_child_optional("rainforest");
		if (!rainforest_node.is_initialized())
		{
			throw std::runtime_error("FailedToFindRainforestNode");
		}
		else
		{
			BOOST_FOREACH(const boost::property_tree::ptree::value_type & v, rainforest_node.get())
			{
				// v.first is the name of the child.
				// v.second is the child tree.

				const std::string_view node_name = v.first;
				const boost::property_tree::ptree node_data = v.second;

				if (0 == v.first.compare("<xmlattr>"))
				{
					ProcessHeaderAttributes(node_data);
					++m_MessageStats.MessageCount;
				}
				else
				{
					switch (string_view_to_fragmenttype(node_name))
					{
					case FragmentTypes::ConnectionStatus:
						BOOST_LOG_TRIVIAL(debug) << L"Processing ConnectionStatus fragment";
						ProcessFragment(ConnectionStatus(node_data));
						++m_MessageStats.ConnectionStatusCount;
						break;

					case FragmentTypes::CurrentSummation:
						BOOST_LOG_TRIVIAL(debug) << L"Processing CurrentSummation fragment";
						ProcessFragment(CurrentSummation(node_data));
						++m_MessageStats.CurrentSummationCount;
						break;

					case FragmentTypes::DeviceInfo:
						BOOST_LOG_TRIVIAL(debug) << L"Processing DeviceInfo fragment";
						ProcessFragment(DeviceInfo(node_data));
						++m_MessageStats.DeviceInfoCount;
						break;

					case FragmentTypes::InstantaneousDemand:
						BOOST_LOG_TRIVIAL(debug) << L"Processing InstantaneousDemand fragment";
						ProcessFragment(InstantaneousDemand(node_data));
						++m_MessageStats.InstantaneousDemandCount;
						break;

					case FragmentTypes::NetworkInfo:
						BOOST_LOG_TRIVIAL(debug) << L"Processing NetworkInfo fragment";
						ProcessFragment(NetworkInfo(node_data));
						++m_MessageStats.NetworkInfoCount;
						break;


					case FragmentTypes::PriceCluster:
						BOOST_LOG_TRIVIAL(debug) << L"Processing PriceCluster fragment";
						ProcessFragment(PriceCluster(node_data));
						++m_MessageStats.PriceClusterCount;
						break;

					case FragmentTypes::BillingPeriodList:
					case FragmentTypes::BlockPriceDetail:
					case FragmentTypes::MessageCluster:
					case FragmentTypes::TimeCluster:
					default:
						BOOST_LOG_TRIVIAL(debug) << L"Ignoring unhandled XML fragments in upload data set (" << v.first << L")";
						break;
					}
				}
			}
		}
	}
	catch (const UnknownFragmentType& ufte)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Unknown fragment type while processing payload...capturing error and re-throwing"; 
		++m_MessageStats.ErrorsWhileProcessing;
		throw;
	}
	catch (const boost::property_tree::ptree_error& pte)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing payload field while processing payload...capturing error and re-throwing";
		++m_MessageStats.MissingPayloadFields;
		++m_MessageStats.ErrorsWhileProcessing;
		throw;
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(trace) << L"General error occurred while processing payload...capturing error and re-throwing";
		++m_MessageStats.ErrorsWhileProcessing;
		throw;
	}
}

void IEagle::ProcessFragment(const ConnectionStatus& connection_status)
{
}

void IEagle::ProcessFragment(const CurrentSummation& current_summation)
{
}

void IEagle::ProcessFragment(const DeviceInfo& device_info)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing model id and version information";
	m_FirmwareVersion = device_info.FirmwareVersion();
	m_HardwareVersion = device_info.HardwareVersion();
	m_ModelId = device_info.ModelId();
}

void IEagle::ProcessFragment(const InstantaneousDemand& instantaneous_demand)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing instantaneous demand history element (" << instantaneous_demand.Now().EnergyValue() << L")";
	m_DemandHistory.insert(std::make_pair(instantaneous_demand.Timestamp(), instantaneous_demand.Now()));
}

void IEagle::ProcessFragment(const NetworkInfo& network_info)
{
	if (!network_info.DeviceMacId().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee End Device (ZED) id in message payload";
	}
	else if (m_ZigbeeMacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee End Device (ZED) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee End Device (ZED) id for Eagle: " << network_info.DeviceMacId();
		m_ZigbeeMacId = network_info.DeviceMacId();
	}

	if (!network_info.CoordinatorZigbeeId().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee Coordinator (ZC) id in message payload";
	}
	else if (m_CoordinatorZigbeeMacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee Coordinator (ZC) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee Coordinator (ZC) id of device forming root with Eagle: " << network_info.CoordinatorZigbeeId();
		m_CoordinatorZigbeeMacId = network_info.CoordinatorZigbeeId();
	}
}

void IEagle::ProcessFragment(const PriceCluster& price_cluster)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing pricing tier and it's price information set";
	m_PricingTiers.insert_or_assign(price_cluster.Tier(), price_cluster.TierPricing());
}

void IEagle::ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes)
{
	// Capture the timestamp for this device payload
	const auto timestamp = header_attributes.get_optional<std::string>("timestamp");
	if (!timestamp.is_initialized())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Missing expected field (timestamp) from payload";
	}
	else
	{
		const auto message_timestamp = hex_string_to_timepoint_since_epoch(timestamp.get());

		if (message_timestamp < m_LastMessageTimestamp)
		{
			BOOST_LOG_TRIVIAL(warning) << L"New message has earlier payload timestamp than previous (out-of-order?)";
		}
		else
		{
			// As expected...message time is moving forward (or, at least, is standing still)...
		}

		m_LastMessageTimestamp = message_timestamp;
	}

	// Capture the device mac id.
	const auto mac_id = header_attributes.get_optional<std::string>("macId");
	if (!mac_id.is_initialized())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Missing expected field (ethernet mac id) from payload";
	}
	else
	{
		m_EthernetMacId = EthernetMacId(mac_id.get());
	}
}

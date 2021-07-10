#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <stdexcept>
#include <string_view>

#include "exceptions/unknown_fragment_type.h"
#include "metering/devices/eagle.h"
#include "metering/fragment_processors/fragment_types.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_devicestats.h"

Eagle::Eagle() :
	ISerializable(),
	m_Connectivity(),
	m_EnergyUsage(),
	m_Statistics(),
	m_EthernetMacId(),
	m_ZigbeeMacId(),
	m_FirmwareVersion(),
	m_HardwareVersion(),
	m_ModelId(),
	m_MeterMessages {
		// Instantiate the various available meter messages queues.
		std::make_pair(Queues::QueueTypes::NotSpecified, MeterMessageQueue()),
		std::make_pair(Queues::QueueTypes::Active, MeterMessageQueue()),
		std::make_pair(Queues::QueueTypes::CancelPending, MeterMessageQueue()),
		std::make_pair(Queues::QueueTypes::Unknown, MeterMessageQueue())
	}
{
}

void Eagle::ProcessPayload(const boost::property_tree::ptree& node)
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
			auto device_stats_notif = std::make_shared<Notification_DeviceStats>(m_EthernetMacId);

			BOOST_FOREACH(const boost::property_tree::ptree::value_type & v, rainforest_node.get())
			{
				// v.first is the name of the child.
				// v.second is the child tree.

				const std::string node_name = v.first;
				const boost::property_tree::ptree node_data = v.second;

				if (0 == v.first.compare("<xmlattr>"))
				{
					ProcessHeaderAttributes(node_data);
					++m_Statistics.MessageCount;
				}
				else
				{
					switch (string_view_to_fragmenttype(node_name))
					{
					case FragmentTypes::BillingPeriodList:
						BOOST_LOG_TRIVIAL(debug) << L"Processing BillingPeriodList fragment";
						ProcessFragment(BillingPeriodList(node_data));
						++m_Statistics.BillingPeriodCount;
						device_stats_notif->BillingPeriodCount(m_Statistics.BillingPeriodCount);
						break;					

					case FragmentTypes::BlockPriceDetail:
						BOOST_LOG_TRIVIAL(debug) << L"Processing BlockPriceDetail fragment";
						ProcessFragment(BlockPriceDetail(node_data));
						++m_Statistics.BlockPriceDetailCount;
						device_stats_notif->BlockPriceDetailCount(m_Statistics.BlockPriceDetailCount);
						break;

					case FragmentTypes::ConnectionStatus:
						BOOST_LOG_TRIVIAL(debug) << L"Processing ConnectionStatus fragment";
						ProcessFragment(ConnectionStatus(node_data));
						++m_Statistics.ConnectionStatusCount;
						device_stats_notif->ConnectionStatusCount(m_Statistics.ConnectionStatusCount);
						break;

					case FragmentTypes::CurrentSummation:
						BOOST_LOG_TRIVIAL(debug) << L"Processing CurrentSummation fragment";
						ProcessFragment(CurrentSummation(node_data));
						++m_Statistics.CurrentSummationCount;
						device_stats_notif->CurrentSummationCount(m_Statistics.CurrentSummationCount);
						break;

					case FragmentTypes::DeviceInfo:
						BOOST_LOG_TRIVIAL(debug) << L"Processing DeviceInfo fragment";
						ProcessFragment(DeviceInfo(node_data));
						++m_Statistics.DeviceInfoCount;
						device_stats_notif->DeviceInfoCount(m_Statistics.DeviceInfoCount);
						break;

					case FragmentTypes::InstantaneousDemand:
						BOOST_LOG_TRIVIAL(debug) << L"Processing InstantaneousDemand fragment";
						ProcessFragment(InstantaneousDemand(node_data));
						++m_Statistics.InstantaneousDemandCount;
						device_stats_notif->InstantaneousDemandCount(m_Statistics.InstantaneousDemandCount);
						break;

					case FragmentTypes::MessageCluster:
						BOOST_LOG_TRIVIAL(debug) << L"Processing MessageCluster fragment";
						ProcessFragment(MessageCluster(node_data));
						++m_Statistics.MessageClusterCount;
						device_stats_notif->MessageClusterCount(m_Statistics.MessageClusterCount);
						break;

					case FragmentTypes::NetworkInfo:
						BOOST_LOG_TRIVIAL(debug) << L"Processing NetworkInfo fragment";
						ProcessFragment(NetworkInfo(node_data));
						++m_Statistics.NetworkInfoCount;
						device_stats_notif->NetworkInfoCount(m_Statistics.NetworkInfoCount);
						break;

					case FragmentTypes::PriceCluster:
						BOOST_LOG_TRIVIAL(debug) << L"Processing PriceCluster fragment";
						ProcessFragment(PriceCluster(node_data));
						++m_Statistics.PriceClusterCount;
						device_stats_notif->PriceClusterCount(m_Statistics.PriceClusterCount);
						break;

					case FragmentTypes::TimeCluster:
						BOOST_LOG_TRIVIAL(debug) << L"Processing TimeCluster fragment";
						++m_Statistics.TimeClusterCount;
						device_stats_notif->TimeClusterCount(m_Statistics.TimeClusterCount);
						break;

					default:
						BOOST_LOG_TRIVIAL(debug) << L"Ignoring unhandled XML fragments in upload data set (" << v.first << L")";
						++m_Statistics.UnknownMessageCount;
						device_stats_notif->UnknownMessageCount(m_Statistics.UnknownMessageCount);
						break;
					}
				}
			}

			// Capture the last message time (i.e. "now").
			m_Statistics.LastMessageTimestamp = std::chrono::system_clock::now();
			device_stats_notif->LastMessageTimestamp(m_Statistics.LastMessageTimestamp);

			// Trigger a notification around the change in device statistics.
			NotificationManagerSingleton()->Dispatch(device_stats_notif);

			// The processing of various fragments may have queued notifications...trigger them.
			NotificationManagerSingleton()->Poll();
		}
	}
	catch (const UnknownFragmentType& ufte)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Unknown fragment type while processing payload...capturing error and re-throwing";
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const boost::property_tree::ptree_error& pte)
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing payload field while processing payload...capturing error and re-throwing";
		++m_Statistics.MissingPayloadFields;
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const std::exception& ex)
	{
		BOOST_LOG_TRIVIAL(trace) << L"General error occurred while processing payload...capturing error and re-throwing";
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
}

void Eagle::ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes)
{
	// Capture the timestamp for this device payload
	const auto timestamp = header_attributes.get_optional<std::string>("timestamp");
	if (!timestamp.is_initialized())
	{
		BOOST_LOG_TRIVIAL(warning) << L"Missing expected field (timestamp) from payload";
	}
	else
	{
		auto message_timestamp = UnixTimepoint(timestamp.get());

		if (message_timestamp < m_Statistics.LastMessageTimestamp)
		{
			BOOST_LOG_TRIVIAL(warning) << L"New message has earlier payload timestamp than previous (out-of-order?)";
		}
		else
		{
			// As expected...message time is moving forward (or, at least, is standing still)...
		}

		m_Statistics.LastMessageTimestamp = message_timestamp;
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

DeviceConnectivity Eagle::Connectivity() const
{
	return m_Connectivity;
}

DeviceEnergyUsage Eagle::EnergyUsage() const
{
	return m_EnergyUsage;
}

DeviceStatistics Eagle::Statistics() const
{
	return m_Statistics;
}

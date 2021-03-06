#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <spdlog/spdlog.h>

#include <stdexcept>
#include <string_view>

#include "exceptions/missing_rainforest_node.h"
#include "exceptions/unknown_fragment_type.h"
#include "metering/devices/rainforest/eagle.h"
#include "metering/devices/rainforest/messages/fragment_types.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "notifications/notification_manager.h"
#include "notifications/metering/notification_devicestats.h"
#include "serialization/rainforest/eagle_serializer.h"

Eagle::Eagle() :
	IDevice()
{
}

void Eagle::ProcessPayload(const boost::property_tree::ptree& node)
{
	try
	{
		const auto rainforest_node = node.get_child_optional("rainforest");
		if (!rainforest_node.is_initialized())
		{
			throw MissingRainforestNode();
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
					switch (Fragments::FromString(node_name))
					{
					case Fragments::FragmentTypes::BillingPeriodList:
						spdlog::debug("Processing BillingPeriodList fragment");
						ProcessFragment(BillingPeriodList(node_data));
						++m_Statistics.BillingPeriodCount;
						device_stats_notif->BillingPeriodCount(m_Statistics.BillingPeriodCount);
						break;					

					case Fragments::FragmentTypes::BlockPriceDetail:
						spdlog::debug("Processing BlockPriceDetail fragment");
						ProcessFragment(BlockPriceDetail(node_data));
						++m_Statistics.BlockPriceDetailCount;
						device_stats_notif->BlockPriceDetailCount(m_Statistics.BlockPriceDetailCount);
						break;

					case Fragments::FragmentTypes::ConnectionStatus:
						spdlog::debug("Processing ConnectionStatus fragment");
						ProcessFragment(ConnectionStatus(node_data));
						++m_Statistics.ConnectionStatusCount;
						device_stats_notif->ConnectionStatusCount(m_Statistics.ConnectionStatusCount);
						break;

					case Fragments::FragmentTypes::CurrentSummation:
						spdlog::debug("Processing CurrentSummation fragment");
						ProcessFragment(CurrentSummation(node_data));
						++m_Statistics.CurrentSummationCount;
						device_stats_notif->CurrentSummationCount(m_Statistics.CurrentSummationCount);
						break;

					case Fragments::FragmentTypes::DeviceInfo:
						spdlog::debug("Processing DeviceInfo fragment");
						ProcessFragment(DeviceInfo(node_data));
						++m_Statistics.DeviceInfoCount;
						device_stats_notif->DeviceInfoCount(m_Statistics.DeviceInfoCount);
						break;

					case Fragments::FragmentTypes::InstantaneousDemand:
						spdlog::debug("Processing InstantaneousDemand fragment");
						ProcessFragment(InstantaneousDemand(node_data));
						++m_Statistics.InstantaneousDemandCount;
						device_stats_notif->InstantaneousDemandCount(m_Statistics.InstantaneousDemandCount);
						break;

					case Fragments::FragmentTypes::MessageCluster:
						spdlog::debug("Processing MessageCluster fragment");
						ProcessFragment(MessageCluster(node_data));
						++m_Statistics.MessageClusterCount;
						device_stats_notif->MessageClusterCount(m_Statistics.MessageClusterCount);
						break;

					case Fragments::FragmentTypes::NetworkInfo:
						spdlog::debug("Processing NetworkInfo fragment");
						ProcessFragment(NetworkInfo(node_data));
						++m_Statistics.NetworkInfoCount;
						device_stats_notif->NetworkInfoCount(m_Statistics.NetworkInfoCount);
						break;

					case Fragments::FragmentTypes::PriceCluster:
						spdlog::debug("Processing PriceCluster fragment");
						ProcessFragment(PriceCluster(node_data));
						++m_Statistics.PriceClusterCount;
						device_stats_notif->PriceClusterCount(m_Statistics.PriceClusterCount);
						break;

					case Fragments::FragmentTypes::TimeCluster:
						spdlog::debug("Processing TimeCluster fragment");
						++m_Statistics.TimeClusterCount;
						device_stats_notif->TimeClusterCount(m_Statistics.TimeClusterCount);
						break;

					default:
						spdlog::debug("Ignoring unhandled XML fragments in upload data set ({})", v.first);
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
		spdlog::trace("Unknown fragment type while processing payload...capturing error and re-throwing");
		spdlog::trace("Exception details: {}", ufte.what());
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const boost::property_tree::ptree_error& pte)
	{
		spdlog::trace("Missing payload field while processing payload...capturing error and re-throwing");
		spdlog::trace("Exception details: {}", pte.what());
		++m_Statistics.MissingPayloadFields;
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
	catch (const std::exception& ex)
	{
		spdlog::trace("General error occurred while processing payload...capturing error and re-throwing");
		spdlog::trace("Exception details: {}", ex.what());
		++m_Statistics.ErrorsWhileProcessing;
		throw;
	}
}

void Eagle::ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes)
{
	// Capture the timestamp for this device payload
	if (const auto timestamp = header_attributes.get_optional<std::string>("timestamp"); !timestamp.is_initialized())
	{
		spdlog::warn("Missing expected field (timestamp) from payload");
	}
	else
	{
		auto message_timestamp = UnixTimepoint(timestamp.get());

		if (message_timestamp < m_Statistics.LastMessageTimestamp)
		{
			spdlog::warn("New message has earlier payload timestamp than previous (out-of-order?)");
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
		spdlog::warn("Missing expected field (ethernet mac id) from payload");
	}
	else
	{
		m_EthernetMacId = EthernetMacId(mac_id.get());
	}
}

const Rainforest::DeviceConnectivity& Eagle::Connectivity() const
{
	return m_Connectivity;
}

const Rainforest::DeviceEnergyUsage& Eagle::EnergyUsage() const
{
	return m_EnergyUsage;
}

const Rainforest::DeviceStatistics& Eagle::Statistics() const
{
	return m_Statistics;
}

const EthernetMacId& Eagle::Ethernet_MacId() const
{
	return m_EthernetMacId;
}

const ZigBeeMacId& Eagle::Zigbee_MacId() const
{
	return m_ZigbeeMacId;
}

const std::string& Eagle::FirmwareVersion() const
{
	return m_FirmwareVersion;
}

const std::string& Eagle::HardwareVersion() const
{
	return m_HardwareVersion;
}

const std::string& Eagle::ModelId() const
{
	return m_ModelId;
}

const PricingTiers& Eagle::PriceTiers() const
{
	return m_PricingTiers;
}

const Eagle::MeterMessagesMap& Eagle::MessageQueues() const
{
	return m_MeterMessages;
}

boost::json::object Eagle::Serialize() const
{
	return Eagle_Serializer(*this).Serialize();
}

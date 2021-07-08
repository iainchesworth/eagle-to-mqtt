#include "metering/common/timestamps.h"
#include "notifications/metering/notification_devicestats.h"

Notification_DeviceStats::Notification_DeviceStats(EthernetMacId device_id) :
	Notification_PublishPayload(device_id)
{
}

Notification_DeviceStats& Notification_DeviceStats::DeviceStats(const DeviceStatistics& statistics)
{
	LastMessageTimestamp(statistics.LastMessageTimestamp);
	MissingPayloadFields(statistics.MissingPayloadFields);
	ErrorsWhileProcessing(statistics.ErrorsWhileProcessing);
	BillingPeriodCount(statistics.BillingPeriodCount);
	BlockPriceDetailCount(statistics.BlockPriceDetailCount);
	ConnectionStatusCount(statistics.ConnectionStatusCount);
	CurrentSummationCount(statistics.CurrentSummationCount);
	DeviceInfoCount(statistics.DeviceInfoCount);
	InstantaneousDemandCount(statistics.InstantaneousDemandCount);
	MessageClusterCount(statistics.MessageClusterCount);
	NetworkInfoCount(statistics.NetworkInfoCount);
	PriceClusterCount(statistics.PriceClusterCount);
	TimeClusterCount(statistics.TimeClusterCount);
	UnknownMessageCount(statistics.UnknownMessageCount);

	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::LastMessageTimestamp(const timepoint_from_epoch& timestamp)
{
	m_ElementsMap.insert(std::make_pair("last_message_timestamp", timestamp));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::MissingPayloadFields(const uint64_t& missing_payload_fields)
{
	m_ElementsMap.insert(std::make_pair("missing_payload_fields", missing_payload_fields));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::ErrorsWhileProcessing(const uint64_t& errors_while_processing)
{
	m_ElementsMap.insert(std::make_pair("last_message_timestamp", errors_while_processing));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::BillingPeriodCount(const uint64_t& last_message_timestamp)
{
	m_ElementsMap.insert(std::make_pair("last_message_timestamp", last_message_timestamp));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::BlockPriceDetailCount(const uint64_t& block_price_detail_count)
{
	m_ElementsMap.insert(std::make_pair("block_price_detail_count", block_price_detail_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::ConnectionStatusCount(const uint64_t& connection_status_count)
{
	m_ElementsMap.insert(std::make_pair("connection_status_count", connection_status_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::CurrentSummationCount(const uint64_t& current_summation_count)
{
	m_ElementsMap.insert(std::make_pair("current_summation_count", current_summation_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::DeviceInfoCount(const uint64_t& device_info_count)
{
	m_ElementsMap.insert(std::make_pair("device_info_count", device_info_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::InstantaneousDemandCount(const uint64_t& instantaneous_demand_count)
{
	m_ElementsMap.insert(std::make_pair("instantaneous_demand_count", instantaneous_demand_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::MessageClusterCount(const uint64_t& message_cluster_count)
{
	m_ElementsMap.insert(std::make_pair("message_cluster_count", message_cluster_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::NetworkInfoCount(const uint64_t& network_info_count)
{
	m_ElementsMap.insert(std::make_pair("network_info_count", network_info_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::PriceClusterCount(const uint64_t& price_cluster_count)
{
	m_ElementsMap.insert(std::make_pair("price_cluster_count", price_cluster_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::TimeClusterCount(const uint64_t& time_cluster_count)
{
	m_ElementsMap.insert(std::make_pair("time_cluster_count", time_cluster_count));
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::UnknownMessageCount(const uint64_t& unknown_message_count)
{
	m_ElementsMap.insert(std::make_pair("unknown_message_count", unknown_message_count));
	return *this;
}

void Notification_DeviceStats::Notify(boost::signals2::signal<NotificationCallback>& signal)
{
	Notification_PublishPayload::Notify(signal);
}

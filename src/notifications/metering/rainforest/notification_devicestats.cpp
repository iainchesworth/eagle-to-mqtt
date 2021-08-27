#include "metering/common/timestamps.h"
#include "notifications/metering/rainforest/notification_devicestats.h"

using namespace Rainforest;

const std::string Notification_DeviceStats::MAPKEY_BILLINGPERIODCOUNT{ "billing_period_count" };
const std::string Notification_DeviceStats::MAPKEY_BLOCKPRICEDETAILCOUNT{ "block_price_detail_count" };
const std::string Notification_DeviceStats::MAPKEY_CONNECTIONSTATUSCOUNT{ "connection_status_count" };
const std::string Notification_DeviceStats::MAPKEY_CURRENTSUMMATIONCOUNT{ "current_summation_count" };
const std::string Notification_DeviceStats::MAPKEY_DEVICEINFOCOUNT{ "device_info_count" };
const std::string Notification_DeviceStats::MAPKEY_INSTANTANEOUSDEMANDCOUNT{ "instantaneous_demand_count" };
const std::string Notification_DeviceStats::MAPKEY_MESSAGECLUSTERCOUNT{ "message_cluster_count" };
const std::string Notification_DeviceStats::MAPKEY_NETWORKINFOCOUNT{ "network_info_count" };
const std::string Notification_DeviceStats::MAPKEY_PRICECLUSTERCOUNT{ "price_cluster_count" };
const std::string Notification_DeviceStats::MAPKEY_TIMECLUSTERCOUNT{ "time_cluster_count" };

Notification_DeviceStats::Notification_DeviceStats(EagleNotification_PublishPayload::Types::DeviceId device_id) :
	Notification_BaseDeviceStats(device_id)
{
}

Notification_DeviceStats& Notification_DeviceStats::DeviceStats(const Rainforest::DeviceStatistics& statistics)
{
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

	Notification_BaseDeviceStats::DeviceStats(statistics);

	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::BillingPeriodCount(const uint64_t& billing_period_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_BILLINGPERIODCOUNT, billing_period_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::BlockPriceDetailCount(const uint64_t& block_price_detail_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_BLOCKPRICEDETAILCOUNT, block_price_detail_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::ConnectionStatusCount(const uint64_t& connection_status_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CONNECTIONSTATUSCOUNT, connection_status_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::CurrentSummationCount(const uint64_t& current_summation_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_CURRENTSUMMATIONCOUNT, current_summation_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::DeviceInfoCount(const uint64_t& device_info_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_DEVICEINFOCOUNT, device_info_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::InstantaneousDemandCount(const uint64_t& instantaneous_demand_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_INSTANTANEOUSDEMANDCOUNT, instantaneous_demand_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::MessageClusterCount(const uint64_t& message_cluster_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_MESSAGECLUSTERCOUNT, message_cluster_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::NetworkInfoCount(const uint64_t& network_info_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_NETWORKINFOCOUNT, network_info_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::PriceClusterCount(const uint64_t& price_cluster_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_PRICECLUSTERCOUNT, price_cluster_count);
	return *this;
}

Notification_DeviceStats& Notification_DeviceStats::TimeClusterCount(const uint64_t& time_cluster_count)
{
	m_ElementsMap.insert_or_assign(MAPKEY_TIMECLUSTERCOUNT, time_cluster_count);
	return *this;
}

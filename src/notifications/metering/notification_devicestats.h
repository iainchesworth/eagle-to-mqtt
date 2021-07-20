#ifndef NOTIFICATION_DEVICESTATS_H
#define NOTIFICATION_DEVICESTATS_H

#include <boost/signals2/signal.hpp>

#include <cstdint>
#include <string>

#include "metering/common/timestamps.h"
#include "metering/devices/rainforest/common/device_stats.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "notifications/metering/notification_publishpayload.h"

class Notification_DeviceStats : public Notification_PublishPayload
{
	static const std::string MAPKEY_LASTMESSAGETIMESTAMP;
	static const std::string MAPKEY_MISSINGPAYLOADFIELDS;
	static const std::string MAPKEY_ERRORSWHILEPROCESSING;
	static const std::string MAPKEY_BILLINGPERIODCOUNT;
	static const std::string MAPKEY_BLOCKPRICEDETAILCOUNT;
	static const std::string MAPKEY_CONNECTIONSTATUSCOUNT;
	static const std::string MAPKEY_CURRENTSUMMATIONCOUNT;
	static const std::string MAPKEY_DEVICEINFOCOUNT;
	static const std::string MAPKEY_INSTANTANEOUSDEMANDCOUNT;
	static const std::string MAPKEY_MESSAGECLUSTERCOUNT;
	static const std::string MAPKEY_NETWORKINFOCOUNT;
	static const std::string MAPKEY_PRICECLUSTERCOUNT;
	static const std::string MAPKEY_TIMECLUSTERCOUNT;
	static const std::string MAPKEY_UNKNOWNMESSAGECOUNT;

public:
	explicit Notification_DeviceStats(EthernetMacId device_id);

public:
	Notification_DeviceStats& DeviceStats(const Rainforest::DeviceStatistics& statistics);

public:
	Notification_DeviceStats& LastMessageTimestamp(const UnixTimepoint& timestamp);
	Notification_DeviceStats& MissingPayloadFields(const uint64_t& missing_payload_fields);
	Notification_DeviceStats& ErrorsWhileProcessing(const uint64_t& errors_while_processing);
	Notification_DeviceStats& BillingPeriodCount(const uint64_t& billing_period_count);
	Notification_DeviceStats& BlockPriceDetailCount(const uint64_t& block_price_detail_count);
	Notification_DeviceStats& ConnectionStatusCount(const uint64_t& connection_status_count);
	Notification_DeviceStats& CurrentSummationCount(const uint64_t& current_summation_count);
	Notification_DeviceStats& DeviceInfoCount(const uint64_t& device_info_count);
	Notification_DeviceStats& InstantaneousDemandCount(const uint64_t& instantaneous_demand_count);
	Notification_DeviceStats& MessageClusterCount(const uint64_t& message_cluster_count);
	Notification_DeviceStats& NetworkInfoCount(const uint64_t& network_info_count);
	Notification_DeviceStats& PriceClusterCount(const uint64_t& price_cluster_count);
	Notification_DeviceStats& TimeClusterCount(const uint64_t& time_cluster_count);
	Notification_DeviceStats& UnknownMessageCount(const uint64_t& unknown_message_count);

private:
	boost::signals2::scoped_connection m_Connection;
	boost::signals2::signal<void()> m_ListenerReceived;
};

#endif // NOTIFICATION_DEVICEINFO_H

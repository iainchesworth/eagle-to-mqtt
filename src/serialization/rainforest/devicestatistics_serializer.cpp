#include <spdlog/spdlog.h>

#include "serialization/rainforest/devicestatistics_serializer.h"

using namespace Rainforest;

DeviceStatistics_Serializer::DeviceStatistics_Serializer(const DeviceStatistics& ds) :
	ISerializer(ds)
{
}

boost::json::object DeviceStatistics_Serializer::Serialize() const
{
	boost::json::object device_stats;

	spdlog::debug("Serializing Rainforest::DeviceStatistics");

	device_stats["LastMessageTimestamp"] = UnixTimepoint::ToString(m_Serializable.LastMessageTimestamp);
	device_stats["TotalMessageCount"] = m_Serializable.TotalMessageCount;
	device_stats["MissingPayloadFields"] = m_Serializable.MissingPayloadFields;
	device_stats["ErrorsWhileProcessing"] = m_Serializable.ErrorsWhileProcessing;
	device_stats["BillingPeriodCount"] = m_Serializable.BillingPeriodCount;
	device_stats["BlockPriceDetailCount"] = m_Serializable.BlockPriceDetailCount;
	device_stats["ConnectionStatusCount"] = m_Serializable.ConnectionStatusCount;
	device_stats["CurrentSummationCount"] = m_Serializable.CurrentSummationCount;
	device_stats["DeviceInfoCount"] = m_Serializable.DeviceInfoCount;
	device_stats["InstantaneousDemandCount"] = m_Serializable.InstantaneousDemandCount;
	device_stats["MessageClusterCount"] = m_Serializable.MessageClusterCount;
	device_stats["NetworkInfoCount"] = m_Serializable.NetworkInfoCount;
	device_stats["PriceClusterCount"] = m_Serializable.PriceClusterCount;
	device_stats["TimeClusterCount"] = m_Serializable.TimeClusterCount;
	device_stats["UnknownMessageCount"] = m_Serializable.UnknownMessageCount;

	return device_stats;
}

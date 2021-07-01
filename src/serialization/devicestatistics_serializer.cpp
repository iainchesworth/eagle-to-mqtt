#include <boost/log/trivial.hpp>

#include "serialization/devicestatistics_serializer.h"

DeviceStatistics_Serializer::DeviceStatistics_Serializer(std::shared_ptr<DeviceStatistics> ds_ptr) :
	ISerializer(ds_ptr)
{
}

boost::json::object DeviceStatistics_Serializer::Serialize() const
{
	auto ds_ptr = std::static_pointer_cast<DeviceStatistics>(m_Serializable);
	boost::json::object device_stats;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing DeviceStatistics";

	device_stats["LastMessageTimestamp"] = Timestamps::ToString(ds_ptr->LastMessageTimestamp);
	device_stats["MessageCount"] = ds_ptr->MessageCount;
	device_stats["MissingPayloadFields"] = ds_ptr->MissingPayloadFields;
	device_stats["ErrorsWhileProcessing"] = ds_ptr->ErrorsWhileProcessing;
	device_stats["BillingPeriodCount"] = ds_ptr->BillingPeriodCount;
	device_stats["BlockPriceDetailCount"] = ds_ptr->BlockPriceDetailCount;
	device_stats["ConnectionStatusCount"] = ds_ptr->ConnectionStatusCount;
	device_stats["CurrentSummationCount"] = ds_ptr->CurrentSummationCount;
	device_stats["DeviceInfoCount"] = ds_ptr->DeviceInfoCount;
	device_stats["InstantaneousDemandCount"] = ds_ptr->InstantaneousDemandCount;
	device_stats["MessageClusterCount"] = ds_ptr->MessageClusterCount;
	device_stats["NetworkInfoCount"] = ds_ptr->NetworkInfoCount;
	device_stats["PriceClusterCount"] = ds_ptr->PriceClusterCount;
	device_stats["TimeClusterCount"] = ds_ptr->TimeClusterCount;
	device_stats["UnknownMessageCount"] = ds_ptr->UnknownMessageCount;

	return device_stats;
}

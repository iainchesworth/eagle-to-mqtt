#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const NetworkInfo& network_info)
{
	if (!network_info.DeviceMacId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee End Device (ZED) id in message payload";
	}
	else if (!network_info.DeviceMacId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee End Device (ZED) id in message payload";
	}
	else if (m_ZigbeeMacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee End Device (ZED) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee End Device (ZED) id for Eagle: " << ZigBeeMacId::ToString(network_info.DeviceMacId().value());
		m_ZigbeeMacId = network_info.DeviceMacId().value();
	}

	if (!network_info.CoordinatorZigbeeId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee Coordinator (ZC) id in message payload";
	}
	else if (!network_info.CoordinatorZigbeeId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee Coordinator (ZC) id in message payload";
	}
	else if (m_Connectivity.ZigBee.Meter_MacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee Coordinator (ZC) id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee Coordinator (ZC) id of device forming root with Eagle: " << ZigBeeMacId::ToString(network_info.CoordinatorZigbeeId().value());
		m_Connectivity.ZigBee.Meter_MacId = network_info.CoordinatorZigbeeId().value();
	}

	if (network_info.Status().has_value()) { m_Connectivity.Status = network_info.Status().value(); }
	if (network_info.Channel().has_value()) { m_Connectivity.Channel = network_info.Channel().value(); }
	if (network_info.LinkStrength().has_value()) { m_Connectivity.LinkStrength = network_info.LinkStrength().value(); }
}

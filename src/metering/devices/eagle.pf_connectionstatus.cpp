#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const ConnectionStatus& connection_status)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter connection details and statistics";

	if (!connection_status.Meter_MacId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing meter Zigbee MAC id in message payload";
	}
	else if (!connection_status.Meter_MacId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid meter Zigbee MAC id in message payload";
	}
	else if (m_Connectivity.ZigBee.Meter_MacId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid meter Zigbee MAC id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee MAC id of meter connected with Eagle: " << ZigBeeMacId::ToString(connection_status.Meter_MacId().value());
		m_Connectivity.ZigBee.Meter_MacId = connection_status.Meter_MacId().value();
	}

	if (!connection_status.Extended_PanId().has_value())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Missing Zigbee network extended PAN id in message payload";
	}
	else if (!connection_status.Extended_PanId().value().IsValid())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Received invalid Zigbee network extended PAN id in message payload";
	}
	else if (m_Connectivity.ZigBee.Extended_PanId.IsValid())
	{
		BOOST_LOG_TRIVIAL(trace) << L"Have already received valid Zigbee network extended PAN id; ignoring";
	}
	else
	{
		BOOST_LOG_TRIVIAL(debug) << L"Capturing Zigbee network extended PAN id: " << ZigBeeMacId::ToString(connection_status.Extended_PanId().value());
		m_Connectivity.ZigBee.Extended_PanId = connection_status.Extended_PanId().value();
	}

	if (connection_status.Status().has_value()) { m_Connectivity.Status = connection_status.Status().value(); }
	if (connection_status.Channel().has_value()) { m_Connectivity.Channel = connection_status.Channel().value(); }
	if (connection_status.LinkStrength().has_value()) { m_Connectivity.LinkStrength = connection_status.LinkStrength().value(); }
}

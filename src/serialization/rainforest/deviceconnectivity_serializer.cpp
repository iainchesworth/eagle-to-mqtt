#include <sstream>

#include "serialization/rainforest/deviceconnectivity_serializer.h"

using namespace Rainforest;

DeviceConnectivity_Serializer::DeviceConnectivity_Serializer(const DeviceConnectivity& dc) :
	ISerializer(dc)
{
}

boost::json::object DeviceConnectivity_Serializer::Serialize() const
{
	boost::json::object device_connectivity;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing Rainforest::DeviceConnectivity";

	device_connectivity["Meter_MacId"] = ZigBeeMacId::ToString(m_Serializable.ZigBee.Meter_MacId);
	device_connectivity["Extended_PanId"] = ZigBeeMacId::ToString(m_Serializable.ZigBee.Extended_PanId);

	std::ostringstream oss;
	oss << m_Serializable.Status;

	device_connectivity["Status"] = oss.str();
	device_connectivity["RadioChannel"] = m_Serializable.Channel;
	device_connectivity["LinkStrength"] = m_Serializable.LinkStrength;

	return device_connectivity;
}

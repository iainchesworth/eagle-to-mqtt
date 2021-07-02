#include <sstream>

#include "serialization/deviceconnectivity_serializer.h"

DeviceConnectivity_Serializer::DeviceConnectivity_Serializer(std::shared_ptr<DeviceConnectivity> dc_ptr) :
	ISerializer(dc_ptr)
{
}

boost::json::object DeviceConnectivity_Serializer::Serialize() const
{
	auto dc_ptr = std::static_pointer_cast<DeviceConnectivity>(m_Serializable);
	boost::json::object device_connectivity;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing DeviceConnectivity";

	device_connectivity["Meter_MacId"] = ZigBeeMacId::ToString(dc_ptr->ZigBee.Meter_MacId);
	device_connectivity["Extended_PanId"] = ZigBeeMacId::ToString(dc_ptr->ZigBee.Extended_PanId);

	std::ostringstream oss;
	oss << dc_ptr->Status;

	device_connectivity["Status"] = oss.str();
	device_connectivity["RadioChannel"] = dc_ptr->Channel;
	device_connectivity["LinkStrength"] = dc_ptr->LinkStrength;

	return device_connectivity;
}

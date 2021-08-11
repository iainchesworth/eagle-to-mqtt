#include <spdlog/spdlog.h>

#include "serialization/fronius/devicestatistics_serializer.h"
#include "serialization/fronius/symo_serializer.h"

Symo_Serializer::Symo_Serializer(const Symo& symo) :
	ISerializer(symo)
{
}

boost::json::object Symo_Serializer::Serialize() const
{
	boost::json::object device_object;

	spdlog::debug("Serializing Symo");

	// Device Statistics
	Fronius::DeviceStatistics_Serializer ds_serializer(m_Serializable.m_Statistics);
	device_object["Stats"] = ds_serializer.Serialize();
	
	return device_object;
}

#include "serialization/bridgestatistics_serializer.h"

BridgeStatistics_Serializer::BridgeStatistics_Serializer(const BridgeStatistics& bs) :
	ISerializer(bs)
{
}

boost::json::object BridgeStatistics_Serializer::Serialize() const
{
	boost::json::object bridge_stats;

	return bridge_stats;
}

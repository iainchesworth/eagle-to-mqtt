#include "bridge/bridge_stats.h"
#include "serialization/bridgestatistics_serializer.h"

BridgeStatistics::BridgeStatistics() :
	ISerializable()
{
}

BridgeStatistics::~BridgeStatistics()
{
}

boost::json::object BridgeStatistics::Serialize() const
{
	return BridgeStatistics_Serializer(*this).Serialize();
}

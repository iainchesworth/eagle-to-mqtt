#include "serialization/bridgestatistics_serializer.h"

BridgeStatistics_Serializer::BridgeStatistics_Serializer(std::shared_ptr<BridgeStatistics> bs_ptr) :
	ISerializer(bs_ptr)
{
}

boost::json::object BridgeStatistics_Serializer::Serialize() const
{
	auto bs_ptr = std::static_pointer_cast<BridgeStatistics>(m_Serializable);
	boost::json::object bridge_stats;



	return bridge_stats;
}

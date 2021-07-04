#include <boost/log/trivial.hpp>

#include "serialization/bridge_serializer.h"
#include "serialization/bridgestatistics_serializer.h"

Bridge_Serializer::Bridge_Serializer(std::shared_ptr<Bridge> bridge_ptr) :
	ISerializer(bridge_ptr)
{
}

boost::json::object Bridge_Serializer::Serialize() const
{
	auto bridge_ptr = std::static_pointer_cast<Bridge>(m_Serializable);
	boost::json::object bridge_object;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing bridge";

	bridge_object["Uptime"] = bridge_ptr->Uptime().count();

	// Bridge Statistics
	BridgeStatistics_Serializer bs_serializer(std::make_shared<BridgeStatistics>(bridge_ptr->Statistics()));
	bridge_object["Stats"] = bs_serializer.Serialize();

	return bridge_object;
}

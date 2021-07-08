#include <boost/log/trivial.hpp>
#include <date/date.h>

#include <sstream>

#include "serialization/bridge_serializer.h"
#include "serialization/bridgestatistics_serializer.h"

Bridge_Serializer::Bridge_Serializer(std::shared_ptr<Bridge> bridge_ptr) :
	ISerializer(bridge_ptr)
{
}

boost::json::object Bridge_Serializer::Serialize() const
{
	using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

	auto bridge_ptr = std::static_pointer_cast<Bridge>(m_Serializable);
	boost::json::object bridge_object;

	BOOST_LOG_TRIVIAL(debug) << L"Serializing bridge";

	// Bridge uptime statistics
	std::ostringstream oss;
	oss << bridge_ptr->Uptime();
	bridge_object["Uptime"] = oss.str();

	// Bridge Statistics
	BridgeStatistics_Serializer bs_serializer(std::make_shared<BridgeStatistics>(bridge_ptr->Statistics()));
	bridge_object["Stats"] = bs_serializer.Serialize();

	return bridge_object;
}

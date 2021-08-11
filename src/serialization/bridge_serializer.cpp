#include <date/date.h>
#include <spdlog/spdlog.h>

#include <sstream>

#include "serialization/bridge_serializer.h"
#include "serialization/bridgestatistics_serializer.h"

Bridge_Serializer::Bridge_Serializer(const Bridge& bridge) :
	ISerializer(bridge)
{
}

boost::json::object Bridge_Serializer::Serialize() const
{
	using namespace date; // Leverage Howard Hinnant's date library to get the iostream support.

	boost::json::object bridge_object;

	spdlog::debug("Serializing bridge");

	// Bridge uptime statistics
	std::ostringstream oss;
	oss << m_Serializable.Uptime();
	bridge_object["Uptime"] = oss.str();

	// Bridge Statistics
	BridgeStatistics_Serializer bs_serializer(m_Serializable.Statistics());
	bridge_object["Stats"] = bs_serializer.Serialize();

	return bridge_object;
}

#include <spdlog/spdlog.h>

#include "metering/devices/fronius/common/ptree_translators.h"
#include "metering/devices/fronius/messages/solarapi_base_message.h"

SolarApi_Base_Message::SolarApi_Base_Message(const boost::property_tree::ptree& node)
{
	spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving inverter timestamp data");
	m_Timestamp = node.get<UnixTimepoint>("Head.Timestamp");
}

const UnixTimepoint& SolarApi_Base_Message::Timestamp() const
{
	return m_Timestamp;
}

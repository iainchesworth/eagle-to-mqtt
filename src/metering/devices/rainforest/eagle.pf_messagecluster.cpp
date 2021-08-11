#include <spdlog/spdlog.h>

#include "metering/devices/rainforest/eagle.h"

void Eagle::ProcessFragment(const MessageCluster& message_cluster)
{
	spdlog::debug("Capturing meter messages intended for the user");
	m_MeterMessages[message_cluster.Queue()].push(message_cluster.Message());
}

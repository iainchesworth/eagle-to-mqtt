#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const MessageCluster& message_cluster)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing meter messages intended for the user";
	m_MeterMessages[message_cluster.Queue()].push(message_cluster.Message());
}

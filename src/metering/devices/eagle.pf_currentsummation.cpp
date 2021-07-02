#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const CurrentSummation& current_summation)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing total summation values (delivered and received)";
	if (current_summation.Delivered().has_value()) { m_EnergyUsage.TotalDelivered = current_summation.Delivered().value(); }
	if (current_summation.Received().has_value()) { m_EnergyUsage.TotalReceived = current_summation.Received().value(); }
}

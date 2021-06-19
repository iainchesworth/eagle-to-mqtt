#include <boost/log/trivial.hpp>
#include <boost/optional/optional.hpp>

#include <cstdint>
#include <sstream>
#include <string_view>

#include "metering/common/unit_converters.h"
#include "metering/fragment_processors/instantaneous_demand.h"

InstantaneousDemand::InstantaneousDemand(const boost::property_tree::ptree& node) :
	IFragmentProcessor(),
	m_DeviceMacId(node.get<std::string>("DeviceMacId")),
	m_MeterMacId(node.get<std::string>("MeterMacId")),
	m_Timestamp(hex_string_to_timepoint(node.get<std::string>("TimeStamp"))),
	m_Demand(
		hex_string_to_uint32_t(node.get<std::string>("Demand")),
		hex_string_to_uint32_t(node.get<std::string>("Multiplier")),
		hex_string_to_uint32_t(node.get<std::string>("Divisor")),
		UnitsOfMeasure::Kilowatts,
		hex_string_to_uint8_t(node.get<std::string>("DigitsRight")),
		hex_string_to_uint8_t(node.get<std::string>("DigitsLeft")),
		string_to_bool(node.get<std::string>("SuppressLeadingZero"))),
	m_Protocol{ IFragmentProcessor::ProcessOptionalProtocol(node) }
{
}

DemandInWatts InstantaneousDemand::Demand() const
{
	return m_Demand;
}

std::chrono::time_point<std::chrono::system_clock> InstantaneousDemand::Timestamp() const
{
	return m_Timestamp;
}

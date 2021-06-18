#include <string>

#include "metering/fragment_processors/current_summation.h"
#include "metering/common/unit_converters.h"

CurrentSummation::CurrentSummation(const boost::property_tree::ptree& node) :
	IFragmentProcessor(),
	m_DeviceMacId(node.get<std::string>("DeviceMacId")),
	m_MeterMacId(node.get<std::string>("MeterMacId")),
	m_TimeStamp(hex_string_to_timepoint(node.get<std::string>("TimeStamp"))),
	m_SummationDelivered(0.0f),
	m_SummationReceived(0.0f),
	m_Protocol{ IFragmentProcessor::ProcessOptionalProtocol(node) }
{
	double summation_delivered = hex_string_to_uint64_t(node.get<std::string>("SummationDelivered"));
	double summation_received = hex_string_to_uint64_t(node.get<std::string>("SummationReceived"));
	const auto multiplier = hex_string_to_uint32_t(node.get<std::string>("Multiplier"));
	const auto divisor = hex_string_to_uint32_t(node.get<std::string>("Divisor"));

	summation_delivered *= (0 == multiplier) ? 1 : multiplier;
	summation_delivered /= (0 == divisor) ? 1 : divisor;
	m_SummationDelivered = summation_delivered;

	summation_received *= (0 == multiplier) ? 1 : multiplier;
	summation_received /= (0 == divisor) ? 1 : divisor;
	m_SummationReceived = summation_received;
}

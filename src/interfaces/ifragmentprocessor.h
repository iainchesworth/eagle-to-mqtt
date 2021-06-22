#ifndef IFRAGMENTPROCESSOR_H
#define IFRAGMENTPROCESSOR_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>

#include "metering/common/protocol_types.h"
#include "metering/common/statuses.h"
#include "metering/fragment_processors/partial_fragment_types/zigbee_mac_id.h"

class IFragmentProcessor
{
protected:
	IFragmentProcessor(const boost::property_tree::ptree& node);

public:
	ZigBeeMacId DeviceMacId() const;

protected:
	ZigBeeMacId m_DeviceMacId;
	ProtocolTypes m_Protocol;

protected:
	Statuses ProcessStatus(const boost::property_tree::ptree& node) const
	{
		auto status = node.get_optional<std::string>("Status");
		if (!status)
		{
			BOOST_LOG_TRIVIAL(trace) << L"No Status tag present in payload...defaulting to NotSpecified";
			return Statuses::StatusTypes::NotSpecified;
		}
		else
		{
			return Statuses(status.value());
		}
	}

private:
	ProtocolTypes ProcessProtocol(const boost::property_tree::ptree& node) const
	{
		auto protocol = node.get_optional<std::string>("Protocol");
		if (!protocol)
		{
			BOOST_LOG_TRIVIAL(trace) << L"No Protocol tag present in payload...defaulting to NotSpecified";
			return ProtocolTypes::NotSpecified;
		}
		else
		{
			return protocol_type_from_string(protocol.value());
		}
	}
};

#endif // IFRAGMENTPROCESSOR_H

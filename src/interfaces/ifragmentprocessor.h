#ifndef IFRAGMENTPROCESSOR_H
#define IFRAGMENTPROCESSOR_H

#include <boost/log/trivial.hpp>
#include <boost/optional/optional.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>

#include "metering/common/protocol_types.h"
#include "metering/common/status_types.h"
#include "metering/common/zigbee_mac_id.h"

class IFragmentProcessor
{
protected:
	template<typename VALUE_TYPE>
	VALUE_TYPE ProcessOptionalTag(const boost::property_tree::ptree& node, const std::string& tag_key, VALUE_TYPE default_value) const
	{
		auto tag = node.get_optional<VALUE_TYPE>(tag_key);
		if (!tag)
		{
			BOOST_LOG_TRIVIAL(trace) << L"No " << tag_key << L" tag present in payload...setting default value";
			return default_value;
		}
		else
		{
			return tag.value();
		}
	}

	template<>
	ZigBeeMacId ProcessOptionalTag(const boost::property_tree::ptree& node, const std::string& tag_key, ZigBeeMacId default_value) const
	{
		auto tag = node.get_optional<ZigBeeMacId>(tag_key, ZigBeeMacId_PropertyTreeTranslator());
		if (!tag)
		{
			BOOST_LOG_TRIVIAL(trace) << L"No " << tag_key << L" tag present in payload...setting default ZigBee MAC id value";
			return default_value;
		}
		else
		{
			return tag.value();
		}
	}

protected:
	ProtocolTypes ProcessOptionalProtocol(const boost::property_tree::ptree& node) const
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

	StatusTypes ProcessOptionalStatus(const boost::property_tree::ptree& node) const
	{
		auto status = node.get_optional<std::string>("Status");
		if (!status)
		{
			BOOST_LOG_TRIVIAL(trace) << L"No Status tag present in payload...defaulting to NotSpecified";
			return StatusTypes::NotSpecified;
		}
		else
		{
			return status_type_from_string(status.value());
		}
	}
};

#endif // IFRAGMENTPROCESSOR_H

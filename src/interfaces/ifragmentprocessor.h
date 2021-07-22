#ifndef IFRAGMENTPROCESSOR_H
#define IFRAGMENTPROCESSOR_H

#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "metering/common/protocols.h"
#include "metering/devices/rainforest/messages/partial_message_types/zigbee_mac_id.h"

class IFragmentProcessor
{
protected:
	explicit IFragmentProcessor(const boost::property_tree::ptree& node);

public:
	std::optional<ZigBeeMacId> DeviceMacId() const;

private:
	std::optional<ZigBeeMacId> m_DeviceMacId;
	std::optional<Protocols> m_Protocol;
};

#endif // IFRAGMENTPROCESSOR_H

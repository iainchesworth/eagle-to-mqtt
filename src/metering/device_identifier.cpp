#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <optional>
#include <string>

#include "metering/device_factory.h"
#include "metering/device_registry.h"
#include "metering/device_identifier.h"
#include "metering/devices/eagle.h"
#include "metering/fragment_processors/partial_fragment_types/ethernet_mac_id.h"
#include "metering/type_handlers/optional.h"

std::shared_ptr<Eagle> IdentifyAndGetDeviceInstance(boost::property_tree::ptree& device_payload)
{
	std::shared_ptr<Eagle> eagle_processor;

	std::optional<std::string> processor_v1; // <sigh> ... yes, the v1 version string is "undefined" (see RFA-Z109 v6 doco)
	std::optional<double> processor_v2;
	std::optional<std::string> raw_ethernet_mac;

	const auto rainforest_child = device_payload.get_child_optional("rainforest");
	if (!rainforest_child)
	{
		BOOST_LOG_TRIVIAL(warning) << L"No version present in the payload; cannot determine device type!";
	}
	else if (raw_ethernet_mac = IsOptional<std::string>(rainforest_child.get(), "<xmlattr>.macId"); !raw_ethernet_mac.has_value())
	{
		BOOST_LOG_TRIVIAL(warning) << L"No ethernet mac id present in the payload; cannot determine device type!";
	}
	else if (processor_v1 = IsOptional<std::string>(rainforest_child.get(), "<xmlattr>.version"); processor_v1.has_value() && (0 == processor_v1.value().compare("undefined")))
	{
		BOOST_LOG_TRIVIAL(debug) << L"Detected RFA-Z109";
		eagle_processor = CheckRegistryAndGetOrCreate<RFA_Z109>(EthernetMacId(raw_ethernet_mac.value()));
	}
	else if (processor_v2 = IsOptional<double>(rainforest_child.get(), "<xmlattr>.version"); processor_v2.has_value() && (2.0 == processor_v2.value()))
	{
		BOOST_LOG_TRIVIAL(debug) << L"Detected EAGLE-200";
		eagle_processor = CheckRegistryAndGetOrCreate<Eagle200>(EthernetMacId(raw_ethernet_mac.value()));
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown version present in the payload; halting processing";
	}

	return eagle_processor;
}

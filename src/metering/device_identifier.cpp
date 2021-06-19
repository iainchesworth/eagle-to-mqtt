#include <boost/optional.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <string>

#include "interfaces/ieagle.h"
#include "metering/common/ethernet_mac_id.h"
#include "metering/device_factory.h"
#include "metering/device_registry.h"
#include "metering/device_identifier.h"

std::shared_ptr<IEagle> IdentifyAndGetDeviceInstance(boost::property_tree::ptree& device_payload)
{
	std::shared_ptr<IEagle> eagle_processor;

	boost::optional<std::string> processor_v1; // <sigh> ... yes, the v1 version string is "undefined" (see RFA-Z109 v6 doco)
	boost::optional<double> processor_v2;
	boost::optional<std::string> raw_ethernet_mac;

	const auto rainforest_child = device_payload.get_child_optional("rainforest");
	if (!rainforest_child)
	{
		BOOST_LOG_TRIVIAL(warning) << L"No version present in the payload; cannot determine device type!";
	}
	else if (raw_ethernet_mac = rainforest_child.get().get_optional<std::string>("<xmlattr>.macId"); !raw_ethernet_mac.is_initialized())
	{
		BOOST_LOG_TRIVIAL(warning) << L"No ethernet mac id present in the payload; cannot determine device type!";
	}
	else if (processor_v1 = rainforest_child.get().get_optional<std::string>("<xmlattr>.version"); processor_v1.is_initialized() && (0 == processor_v1.get().compare("undefined")))
	{
		BOOST_LOG_TRIVIAL(debug) << L"Detected RFA-Z109";
		eagle_processor = CheckRegistryAndGetOrCreate<RFA_Z109>(EthernetMacId(raw_ethernet_mac.get()));
	}
	else if (processor_v2 = rainforest_child.get().get_optional<double>("<xmlattr>.version"); processor_v2.is_initialized() && (2.0 == processor_v2.get()))
	{
		BOOST_LOG_TRIVIAL(debug) << L"Detected EAGLE-200";
		eagle_processor = CheckRegistryAndGetOrCreate<Eagle200>(EthernetMacId(raw_ethernet_mac.get()));
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown version present in the payload; halting processing";
	}

	return eagle_processor;
}

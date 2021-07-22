#include <boost/core/ignore_unused.hpp>
#include <boost/log/trivial.hpp>
#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <optional>
#include <string>

#include "interfaces/idevice.h"
#include "metering/device_factory.h"
#include "metering/device_registry.h"
#include "metering/device_identifier.h"
#include "metering/devices/fronius/symo.h"
#include "metering/devices/rainforest/eagle.h"
#include "metering/devices/rainforest/eagle-200/eagle_200.h"
#include "metering/devices/rainforest/rfa-z109/rfa_z109.h"
#include "metering/devices/rainforest/messages/partial_message_types/ethernet_mac_id.h"
#include "metering/types/optional.h"

std::shared_ptr<IDevice> IdentifyAndGetEagleInstance(const boost::property_tree::ptree& device_payload)
{
	std::shared_ptr<IDevice> processor;

	std::optional<std::string> processor_v1; // <sigh> ... yes, the v1 version string is "undefined" (see RFA-Z109 v6 doco)
	std::optional<double> processor_v2;
	std::optional<std::string> raw_ethernet_mac;

	if (const auto rainforest_child = device_payload.get_child_optional("rainforest"); !rainforest_child)
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
		processor = DeviceRegistrySingleton()->GetOrCreate<RFA_Z109>(EthernetMacId(raw_ethernet_mac.value()));
	}
	else if (processor_v2 = IsOptional<double>(rainforest_child.get(), "<xmlattr>.version"); processor_v2.has_value() && (2.0 == processor_v2.value()))
	{
		BOOST_LOG_TRIVIAL(debug) << L"Detected EAGLE-200";
		processor = DeviceRegistrySingleton()->GetOrCreate<Eagle200>(EthernetMacId(raw_ethernet_mac.value()));
	}
	else
	{
		BOOST_LOG_TRIVIAL(warning) << L"Unknown version present in the payload; halting processing";
	}

	return processor;
}

std::shared_ptr<IDevice> IdentifyAndGetSymoInstance(const boost::property_tree::ptree& device_payload)
{
	boost::ignore_unused(device_payload);

	std::shared_ptr<IDevice> processor = DeviceRegistrySingleton()->GetOrCreate<Symo>(EthernetMacId());

	return processor;
}

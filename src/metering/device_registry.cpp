#include <boost/log/trivial.hpp>

#include "metering/device_registry.h"

DeviceRegistry::DeviceRegistry()
{
	BOOST_LOG_TRIVIAL(debug) << L"Initialising the DeviceRegistry";
}

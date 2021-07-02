#include <boost/log/trivial.hpp>

#include "metering/devices/eagle.h"

void Eagle::ProcessFragment(const DeviceInfo& device_info)
{
	BOOST_LOG_TRIVIAL(debug) << L"Capturing model id and version information";
	if (device_info.FirmwareVersion().has_value()) { m_FirmwareVersion = device_info.FirmwareVersion().value(); }
	if (device_info.HardwareVersion().has_value()) { m_HardwareVersion = device_info.HardwareVersion().value(); }
	if (device_info.ModelId().has_value()) { m_ModelId = device_info.ModelId().value(); }
}

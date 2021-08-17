#include "metering/devices/fronius/hardware/hardware.h"

HardwareBase::HardwareBase(bool is_installed) :
	m_IsInstalled(is_installed)
{
}

bool HardwareBase::IsInstalled() const
{
	return m_IsInstalled;
}

std::ostream& operator<<(std::ostream& os, const HardwareBase& hardware_base)
{
	os << hardware_base.DeviceType() << " is" << (hardware_base.IsInstalled() ? "" : " NOT") << " installed";
	return os;
}

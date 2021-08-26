#include "metering/devices/fronius/common/symo_payloads.h"

SymoPayload::SymoPayload(const HardwareBase::HardwareId& id) :
	m_Id(id)
{
}

HardwareBase::HardwareId SymoPayload::Id() const
{
	return m_Id;
}

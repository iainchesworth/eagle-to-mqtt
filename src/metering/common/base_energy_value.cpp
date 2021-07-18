#include "metering/common/base_energy_value.h"

BaseEnergyValue::BaseEnergyValue() :
	m_EnergyValue(0.0f)
{
}

BaseEnergyValue::BaseEnergyValue(double energy_value) :
	m_EnergyValue(energy_value)
{
}

double BaseEnergyValue::EnergyValue() const
{
	return m_EnergyValue;
}

#include "metering/devices/fronius/energy_management/akku_energy_measurement.h"

AkkuEnergyMeasurement::AkkuEnergyMeasurement(const std::string& akku_energy_measurement) :
	EnergyMeasurementBase<Battery, ChargeFlow>(akku_energy_measurement)
{
}

#include "metering/devices/fronius/energy_management/pv_energy_measurement.h"

PVEnergyMeasurement::PVEnergyMeasurement(const std::string& pv_energy_measurement) :
	EnergyMeasurementBase<Inverter, ProductionFlow>(pv_energy_measurement)
{
}

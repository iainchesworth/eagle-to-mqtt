#include "metering/devices/fronius/energy_measurement/energy_measurement.h"

GridEnergyMeasurement::GridEnergyMeasurement(const std::string& grid_energy_measurement) :
	EnergyMeasurementBase<SmartMeter, GridFlow>(grid_energy_measurement)
{
}

LoadEnergyMeasurement::LoadEnergyMeasurement(const std::string& load_energy_measurement) :
	EnergyMeasurementBase<SmartMeter, LoadFlow>(load_energy_measurement)
{
}

AkkuEnergyMeasurement::AkkuEnergyMeasurement(const std::string& akku_energy_measurement) :
	EnergyMeasurementBase<Battery, ChargeFlow>(akku_energy_measurement)
{
}

PVEnergyMeasurement::PVEnergyMeasurement(const std::string& pv_energy_measurement) :
	EnergyMeasurementBase<Inverter, ProductionFlow>(pv_energy_measurement)
{
}

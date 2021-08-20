#include "metering/devices/fronius/energy_management/load_energy_measurement.h"

LoadEnergyMeasurement::LoadEnergyMeasurement(const std::string& load_energy_measurement) :
	EnergyMeasurementBase<SmartMeter, LoadFlow>(load_energy_measurement)
{
}

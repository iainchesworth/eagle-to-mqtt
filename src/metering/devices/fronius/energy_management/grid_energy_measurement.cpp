#include "metering/devices/fronius/energy_management/grid_energy_measurement.h"

GridEnergyMeasurement::GridEnergyMeasurement(const std::string& grid_energy_measurement) :
	EnergyMeasurementBase<SmartMeter, GridFlow>(grid_energy_measurement)
{
}

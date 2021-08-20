#ifndef GRID_ENERGY_MEASUREMENT_H
#define GRID_ENERGY_MEASUREMENT_H

#include <string>

#include "metering/devices/fronius/energy_management/energy_measurement.h"
#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"
#include "metering/devices/fronius/hardware/smart_meter.h"

class GridEnergyMeasurement : public EnergyMeasurementBase<SmartMeter, GridFlow>
{
public:
	GridEnergyMeasurement(const std::string& grid_energy_measurement);
};


#endif // GRID_ENERGY_MEASUREMENT_H

#ifndef LOAD_ENERGY_MEASUREMENT_H
#define LOAD_ENERGY_MEASUREMENT_H

#include <string>

#include "metering/devices/fronius/energy_management/energy_measurement.h"
#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"
#include "metering/devices/fronius/hardware/smart_meter.h"

class LoadEnergyMeasurement : public EnergyMeasurementBase<SmartMeter, LoadFlow>
{
public:
	LoadEnergyMeasurement(const std::string& load_energy_measurement);
};

#endif // LOAD_ENERGY_MEASUREMENT_H

#ifndef PV_ENERGY_MEASUREMENT_H
#define PV_ENERGY_MEASUREMENT_H

#include <string>

#include "metering/devices/fronius/energy_management/energy_measurement.h"
#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"
#include "metering/devices/fronius/hardware/inverter.h"

class PVEnergyMeasurement : public EnergyMeasurementBase<Inverter, ProductionFlow>
{
public:
	PVEnergyMeasurement(const std::string& pv_energy_measurement);
};

#endif // PV_ENERGY_MEASUREMENT_H

#ifndef AKKU_ENERGY_MEASUREMENT_H
#define AKKU_ENERGY_MEASUREMENT_H

#include <string>

#include "metering/devices/fronius/energy_management/energy_measurement.h"
#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"
#include "metering/devices/fronius/hardware/battery.h"

class AkkuEnergyMeasurement : public EnergyMeasurementBase<Battery, ChargeFlow>
{
public:
	AkkuEnergyMeasurement(const std::string& akku_energy_measurement);
};

#endif // AKKU_ENERGY_MEASUREMENT_H

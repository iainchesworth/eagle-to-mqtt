#ifndef INVERTER_GENERATION_DATA_H
#define INVERTER_GENERATION_DATA_H

#include <unordered_map>

#include "metering/devices/fronius/energy_management/energy_production_stats.h"
#include "metering/devices/fronius/hardware/hardware.h"

using InverterGenerationData = std::unordered_map<HardwareBase::HardwareId, Fronius::EnergyProductionStats>;

#endif // INVERTER_GENERATION_DATA_H

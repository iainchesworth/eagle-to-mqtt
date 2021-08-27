#ifndef ENERGY_PRODUCTION_H
#define ENERGY_PRODUCTION_H

#include <boost/json.hpp>

#include "interfaces/iserializable.h"
#include "metering/devices/fronius/energy_management/energy_production_stats.h"
#include "metering/devices/fronius/messages_types/inverter_data.h"
#include "metering/devices/fronius/messages_types/inverter_generation_data.h"

namespace Fronius
{

class EnergyProduction : public ISerializable
{
public:
	EnergyProduction();
	virtual ~EnergyProduction() = default;

public:
	InverterGenerationData Inverters;
	EnergyProductionStats Site;

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Fronius

#endif // ENERGY_PRODUCTION_H

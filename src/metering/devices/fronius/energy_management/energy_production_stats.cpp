#include "metering/devices/fronius/energy_management/energy_production_stats.h"
#include "serialization/fronius/energyproductionstats_serializer.h"

using namespace Fronius;

EnergyProductionStats::EnergyProductionStats()
{
}

boost::json::object EnergyProductionStats::Serialize() const
{
	return EnergyProductionStats_Serializer(*this).Serialize();
}

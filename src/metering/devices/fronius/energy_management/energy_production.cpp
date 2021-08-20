#include "metering/devices/fronius/energy_management/energy_production.h"
#include "serialization/fronius/energyproduction_serializer.h"

using namespace Fronius;

EnergyProduction::EnergyProduction()
{
}

boost::json::object Fronius::EnergyProduction::Serialize() const
{
	return EnergyProduction_Serializer(*this).Serialize();
}

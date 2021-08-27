#include <spdlog/spdlog.h>

#include "serialization/fronius/energyproduction_serializer.h"

using namespace Fronius;

EnergyProduction_Serializer::EnergyProduction_Serializer(const EnergyProduction& ep) :
	ISerializer(ep)
{
}

boost::json::object EnergyProduction_Serializer::Serialize() const
{
	boost::json::object energy_production;

	spdlog::debug("Serializing Fronius::EnergyProduction_Serializer");

	return energy_production;
}

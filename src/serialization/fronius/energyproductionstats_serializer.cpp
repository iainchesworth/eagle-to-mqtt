#include <spdlog/spdlog.h>

#include "serialization/fronius/energyproductionstats_serializer.h"

using namespace Fronius;

EnergyProductionStats_Serializer::EnergyProductionStats_Serializer(const EnergyProductionStats& eps) :
	ISerializer(eps)
{
}

boost::json::object EnergyProductionStats_Serializer::Serialize() const
{
	boost::json::object energy_production_stats;

	spdlog::debug("Serializing Fronius::EnergyProductionStats_Serializer");

	return energy_production_stats;
}

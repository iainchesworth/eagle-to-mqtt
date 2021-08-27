#ifndef ENERGYPRODUCTIONSTATS_SERIALIZER_H
#define ENERGYPRODUCTIONSTATS_SERIALIZER_H

#include <boost/json.hpp>

#include "interfaces/iserializer.h"
#include "metering/devices/fronius/energy_management/energy_production_stats.h"

namespace Fronius
{

class EnergyProductionStats_Serializer : public ISerializer<EnergyProductionStats>
{
public:
	explicit EnergyProductionStats_Serializer(const EnergyProductionStats& eps);

public:
	boost::json::object Serialize() const final;
};

}
// namespace Fronius

#endif // ENERGYPRODUCTIONSTATS_SERIALIZER_H

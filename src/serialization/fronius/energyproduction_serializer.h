#ifndef ENERGYPRODUCTION_SERIALIZER_H
#define ENERGYPRODUCTION_SERIALIZER_H

#include <boost/json.hpp>

#include "interfaces/iserializer.h"
#include "metering/devices/fronius/energy_management/energy_production.h"

namespace Fronius
{

class EnergyProduction_Serializer : public ISerializer<EnergyProduction>
{
public:
	explicit EnergyProduction_Serializer(const EnergyProduction& ep);

public:
	boost::json::object Serialize() const final;
};

}
// namespace Fronius


#endif // ENERGYPRODUCTION_SERIALIZER_H

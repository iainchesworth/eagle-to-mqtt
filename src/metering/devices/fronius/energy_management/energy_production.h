#ifndef ENERGY_PRODUCTION_H
#define ENERGY_PRODUCTION_H

#include <boost/json.hpp>

#include <cstdint>
#include <vector>

#include "interfaces/iserializable.h"
#include "metering/devices/fronius/energy_management/energy_production_stats.h"

namespace Fronius
{

class EnergyProduction : public ISerializable
{
public:
	EnergyProduction();
	virtual ~EnergyProduction() = default;

public:
	std::vector<EnergyProductionStats> Inverters;
	EnergyProductionStats Site;

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Fronius

#endif // ENERGY_PRODUCTION_H

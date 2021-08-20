#ifndef ENERGY_PRODUCTION_STATS_H
#define ENERGY_PRODUCTION_STATS_H

#include <boost/json.hpp>

#include "interfaces/iserializable.h"
#include "metering/common/energy_value.h"

namespace Fronius
{

class EnergyProductionStats : public ISerializable
{
public:
	EnergyProductionStats();
	virtual ~EnergyProductionStats() = default;

public:
	Production Today{ 0.0f };
	Production Year{ 0.0f };
	Production AllTime{ 0.0f };

public:
	virtual boost::json::object Serialize() const;
};

}
// namespace Fronius

#endif // ENERGY_PRODUCTION_STATS_H

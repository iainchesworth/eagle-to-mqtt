#ifndef BRIDGE_STATS_H
#define BRIDGE_STATS_H

#include "interfaces/iserializable.h"

class BridgeStatistics : public ISerializable
{
public:
	BridgeStatistics();
	virtual ~BridgeStatistics() = default;

public:
	boost::json::object Serialize() const final;
};

#endif // BRIDGE_STATS_H

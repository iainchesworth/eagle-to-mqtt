#ifndef BRIDGE_STATS_H
#define BRIDGE_STATS_H

#include "interfaces/iserializable.h"

class BridgeStatistics : public ISerializable
{
public:
	BridgeStatistics();
	virtual ~BridgeStatistics();

public:
	virtual boost::json::object Serialize() const;
};

#endif // BRIDGE_STATS_H

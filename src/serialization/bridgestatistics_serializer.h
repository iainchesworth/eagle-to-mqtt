#ifndef BRIDGESTATISTICS_SERIALIZER_H
#define BRIDGESTATISTICS_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "bridge/bridge_stats.h"

class BridgeStatistics_Serializer : public ISerializer
{
public:
	BridgeStatistics_Serializer(std::shared_ptr<BridgeStatistics> bs_ptr);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // BRIDGESTATISTICS_SERIALIZER_H

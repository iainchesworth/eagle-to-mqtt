#ifndef BRIDGE_SERIALIZER_H
#define BRIDGE_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "bridge/bridge.h"

class Bridge_Serializer : public ISerializer<Bridge>
{
public:
	explicit Bridge_Serializer(const Bridge& bridge);

public:
	boost::json::object Serialize() const final;
};

#endif // BRIDGE_SERIALIZER_H

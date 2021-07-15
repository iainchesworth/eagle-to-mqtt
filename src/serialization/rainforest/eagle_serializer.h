#ifndef EAGLE_SERIALIZER_H
#define EAGLE_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/rainforest/eagle.h"

class Eagle_Serializer : public ISerializer<Eagle>
{
public:
	Eagle_Serializer(const Eagle& eagle);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // EAGLE_SERIALIZER_H

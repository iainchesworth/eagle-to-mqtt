#ifndef EAGLE_SERIALIZER_H
#define EAGLE_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/eagle.h"

class Eagle_Serializer : public ISerializer
{
public:
	Eagle_Serializer(std::shared_ptr<Eagle> eagle_ptr);

public:
	virtual boost::json::object Serialize() const final;
};

#endif // EAGLE_SERIALIZER_H

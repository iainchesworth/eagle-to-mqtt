#ifndef SYMO_SERIALIZER_H
#define SYMO_SERIALIZER_H

#include <boost/json.hpp>

#include <memory>

#include "interfaces/iserializer.h"
#include "metering/devices/fronius/symo.h"

class Symo_Serializer : public ISerializer<Symo>
{
public:
	explicit Symo_Serializer(const Symo& symo);

public:
	boost::json::object Serialize() const final;
};

#endif // SYMO_SERIALIZER_H

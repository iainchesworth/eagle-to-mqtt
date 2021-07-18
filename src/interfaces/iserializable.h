#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <boost/json.hpp>

#include "interfaces/iserializer.h"

class ISerializable
{
public:
	ISerializable();

public:
	virtual boost::json::object Serialize() const = 0;
};

#endif // ISERIALIZABLE_H

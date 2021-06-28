#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <boost/json.hpp>

// Forward interface definitions
class ISerializable;

class ISerializer
{
public:
	ISerializer(std::shared_ptr<ISerializable> serializable_class);

public:
	virtual boost::json::object Serialize() const = 0;

protected:
	std::shared_ptr<ISerializable> m_Serializable;
};

#endif // ISERIALIZER_H

#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <boost/json.hpp>

template<typename SERIALIZABLE_TYPE>
class ISerializer
{
public:
	explicit ISerializer(const SERIALIZABLE_TYPE& serializable_class) :
		m_Serializable(serializable_class)
	{
	}

public:
	virtual boost::json::object Serialize() const = 0;

protected:
	const SERIALIZABLE_TYPE& m_Serializable;
};

#endif // ISERIALIZER_H

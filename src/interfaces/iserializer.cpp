#include "interfaces/iserializable.h"
#include "interfaces/iserializer.h"

ISerializer::ISerializer(std::shared_ptr<ISerializable> serializable_class) :
	m_Serializable(serializable_class)
{
}

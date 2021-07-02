#ifndef ESSENTIAL_H
#define ESSENTIAL_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "metering/type_handlers/presence_helpers.h"

template<typename FIELD_TYPE>
FIELD_TYPE IsEssential(const boost::property_tree::ptree& node, const std::string& field)
{
	return PresenseHelpers::RetrieveValue<FIELD_TYPE>(node, field);
}

#endif // ESSENTIAL_H

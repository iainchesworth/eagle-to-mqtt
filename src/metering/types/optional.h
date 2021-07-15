#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "metering/types/presence_helpers.h"

template<typename FIELD_TYPE>
std::optional<FIELD_TYPE> IsOptional(const boost::property_tree::ptree& node, const std::string& field)
{
	return PresenseHelpers::TryAndRetrieveValue<FIELD_TYPE>(node, field);
}

template<typename FIELD_TYPE>
FIELD_TYPE IsOptionalWithDefault(const boost::property_tree::ptree& node, const std::string& field, FIELD_TYPE default_value)
{
	return IsOptional<FIELD_TYPE>(node, field).value_or(default_value);
}

#endif // OPTIONAL_H

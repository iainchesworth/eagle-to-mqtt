#ifndef SYMO_PAYLOADS_H
#define SYMO_PAYLOADS_H

#include <boost/property_tree/ptree.hpp>
#include <spdlog/spdlog.h>

#include <optional>
#include <string>
#include <type_traits>

#include "metering/devices/fronius/common/ptree_translators.h"
#include "utils/is_optional.h"

class SymoPayload
{
public:
	template<typename VARIANT_TYPE, std::enable_if_t<is_optional<typename std::decay_t<VARIANT_TYPE>>::value, bool> = true>
	static void GetField(const std::string& field_name, VARIANT_TYPE& field_element, const boost::property_tree::ptree& node)
	{
		spdlog::debug("Attempting to extract optional field {} (of type {}) from message payload", field_name, typeid(typename VARIANT_TYPE::value_type).name());
		if (auto field_value = node.get_optional<typename VARIANT_TYPE::value_type>(field_name); field_value.is_initialized())
		{
			// Convert from boost::optional to std::optional (transporting the internal value);
			field_element = VARIANT_TYPE(field_value.get());
		}
		else
		{
			// Convert from boost::optional to std::optional (without an internal value);
			field_element = VARIANT_TYPE();
		}
	}

	template<typename VARIANT_TYPE, std::enable_if_t<!is_optional<typename std::decay_t<VARIANT_TYPE>>::value, bool> = true>
	static void GetField(const std::string& field_name, VARIANT_TYPE& field_element, const boost::property_tree::ptree& node)
	{
		try
		{
			spdlog::debug("Attempting to extract field {} (of type {}) from message payload", field_name, typeid(VARIANT_TYPE).name());
			field_element = node.get<VARIANT_TYPE>(field_name);
		}
		catch (const boost::property_tree::ptree_error& pt_err)
		{
			spdlog::debug("Failed to extract field {}; error was: {}", field_name, pt_err.what());
		}
	}
};


#endif // SYMO_PAYLOADS_H

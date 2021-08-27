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
	SymoPayload(const HardwareBase::HardwareId& id);

public:
	HardwareBase::HardwareId Id() const;

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

	template<typename MAP_TYPE>
	static void Collection_GetField(const std::string& field_name, MAP_TYPE& map_to_store_values, const boost::property_tree::ptree& node)
	{
		const auto production_node = node.get_child_optional(field_name);
		if (!production_node.is_initialized())
		{
			spdlog::debug("SolarApi_CurrentData_Inverter() - no {} information to process", field_name);
		}
		else
		{
			for (const auto& [inverter_string_id, power_value] : production_node.value().get_child("Values"))
			{
				using member_map_value_type = typename std::remove_reference<decltype(map_to_store_values)>::type::value_type;

				auto inverter_id = std::stoul(inverter_string_id);
				auto production = typename member_map_value_type::second_type(power_value.get_value<double>());

				map_to_store_values.insert_or_assign(inverter_id, production);
			}
		}
	}

private:
	HardwareBase::HardwareId m_Id;
};


#endif // SYMO_PAYLOADS_H

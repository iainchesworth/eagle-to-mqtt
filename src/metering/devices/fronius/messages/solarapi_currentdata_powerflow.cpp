#include <spdlog/spdlog.h>

#include <cstdint>
#include <string>

#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"

SolarApi_CurrentData_PowerFlow::SolarApi_CurrentData_PowerFlow(const boost::property_tree::ptree& node) :
	m_PowerFlowVersion(node.get<uint32_t>("Body.Version")),
	m_LocalSite(Site::ExtractFromPayload(node.get_child("Body.Site"), m_PowerFlowVersion)),
	m_Inverters{}
{
	ProcessPayload_Inverters(node);

	if (PowerFlowVersions::Versions::Version10 <= m_PowerFlowVersion)
	{
		ProcessPayload_SmartLoads(node);

		if (PowerFlowVersions::Versions::Version11 <= m_PowerFlowVersion)
		{
			ProcessPayload_SecondaryMeters(node);
		}
	}
}

void SolarApi_CurrentData_PowerFlow::ProcessPayload_Inverters(const boost::property_tree::ptree& node)
{
	const auto inverter_node = node.get_child_optional("Body.Inverters");
	if (!inverter_node.is_initialized())
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow: no inverter information found");
	}
	else
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving inverter data");

		for (const auto& [elem_name, elem_node] : inverter_node.value())
		{
			try
			{
				HardwareBase::HardwareId id = std::stoull(elem_name);
				m_Inverters.insert_or_assign(id, InverterData::ExtractFromPayload(elem_node, id));
			}
			catch (const std::invalid_argument& ex_ia)
			{
				spdlog::warn("Failed to convert inverter id: {}", elem_name);
			}
			catch (const std::out_of_range& ex_oor)
			{
				spdlog::warn("Inverter id cannot be represented in internal type; provided id was {}", elem_name);
			}
		}
	}
}

void SolarApi_CurrentData_PowerFlow::ProcessPayload_SmartLoads(const boost::property_tree::ptree& node)
{
	const auto smartload_node = node.get_child_optional("Body.Smartloads");
	if (!smartload_node.is_initialized())
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow: no smart load information found");
	}
	else
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving smart load data");

		for (const auto& [elem_name, elem_node] : smartload_node.value())
		{
			///FIXME m_SmartLoads.push_back(SmartLoad::ExtractFromPayload(elem_node));
		}
	}
}

void SolarApi_CurrentData_PowerFlow::ProcessPayload_SecondaryMeters(const boost::property_tree::ptree& node)
{
	const auto secondary_meters = node.get_child_optional("Body.SecondaryMeters");
	if (!secondary_meters.is_initialized())
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow: no secondary meter information found");
	}
	else
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving secondary meter data");

		for (const auto& [elem_name, elem_node] : secondary_meters.value())
		{
			///FIXME m_SecondaryMeters.push_back(SecondaryMeter::ExtractFromPayload(elem_node));
		}
	}
}

PowerFlowVersions SolarApi_CurrentData_PowerFlow::PowerFlowVersion() const
{
	return m_PowerFlowVersion;
}

const Site& SolarApi_CurrentData_PowerFlow::LocalSite() const
{
	return m_LocalSite;
}

const std::unordered_map<HardwareBase::HardwareId, InverterData>& SolarApi_CurrentData_PowerFlow::Inverters() const
{
	return m_Inverters;
}

const std::unordered_map<HardwareBase::HardwareId, SecondaryMeterData>& SolarApi_CurrentData_PowerFlow::SecondaryMeters() const
{
	return m_SecondaryMeters;
}

const std::unordered_map<HardwareBase::HardwareId, SmartLoadData>& SolarApi_CurrentData_PowerFlow::SmartLoads() const
{
	return m_SmartLoads;
}

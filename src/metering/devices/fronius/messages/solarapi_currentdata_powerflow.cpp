#include <spdlog/spdlog.h>

#include <cstdint>

#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"

SolarApi_CurrentData_PowerFlow::SolarApi_CurrentData_PowerFlow(const boost::property_tree::ptree& node) :
	m_PowerFlowVersion(node.get<uint32_t>("Body.Version")),
	m_LocalSite(Site::ExtractFromPayload(node.get_child("Body.Site"), m_PowerFlowVersion)),
	m_Inverters{}
{
	const auto inverter_node = node.get_child_optional("Body.Inverters");
	if (!inverter_node.is_initialized())
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow: no inverter information found");
	}
	else
	{
		spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving inverter data");

		for(const auto& [elem_name, elem_node] : inverter_node.value())
		{
			m_Inverters.push_back(InverterData::ExtractFromPayload(elem_node));
		}
	}

	if (PowerFlowVersions::Versions::Version10 <= m_PowerFlowVersion)
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
				m_SmartLoads.push_back(SmartLoad::ExtractFromPayload(elem_node));
			}
		}

		if (PowerFlowVersions::Versions::Version11 <= m_PowerFlowVersion)
		{
			const auto secondary_meters = node.get_child_optional("Body.SecondaryMeters");
			if (!secondary_meters.is_initialized())
			{
				spdlog::debug("SolarApi_CurrentData_PowerFlow: no secondary meter information found");
			}
			else
			{
				spdlog::debug("SolarApi_CurrentData_PowerFlow - Retrieving secondary meter data");

				for (const auto& [elem_name, elem_node] : smartload_node.value())
				{
					m_SecondaryMeters.push_back(SecondaryMeter::ExtractFromPayload(elem_node));
				}
			}
		}
	}
}

PowerFlowVersions SolarApi_CurrentData_PowerFlow::PowerFlowVersion() const
{
	return m_PowerFlowVersion;
}

Site SolarApi_CurrentData_PowerFlow::LocalSite() const
{
	return m_LocalSite;
}

std::vector<InverterData> SolarApi_CurrentData_PowerFlow::Inverters() const
{
	return m_Inverters;
}

std::vector<SecondaryMeter> SolarApi_CurrentData_PowerFlow::SecondaryMeters() const
{
	return m_SecondaryMeters;
}

std::vector<SmartLoad> SolarApi_CurrentData_PowerFlow::SmartLoads() const
{
	return m_SmartLoads;
}

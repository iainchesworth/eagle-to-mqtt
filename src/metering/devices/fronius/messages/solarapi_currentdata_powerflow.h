#ifndef SOLARAPI_CURRENTDATA_POWERFLOW_H
#define SOLARAPI_CURRENTDATA_POWERFLOW_H

#include <boost/property_tree/ptree.hpp>

#include <cstdint>
#include <vector>

#include "metering/devices/fronius/messages_types/inverter_data.h"
#include "metering/devices/fronius/messages_types/powerflow_versions.h"
#include "metering/devices/fronius/messages_types/secondary_meters.h"
#include "metering/devices/fronius/messages_types/smartload.h"
#include "metering/devices/fronius/site/site.h"

class SolarApi_CurrentData_PowerFlow
{
public:
	explicit SolarApi_CurrentData_PowerFlow(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_PowerFlow() = default;

public:
	PowerFlowVersions PowerFlowVersion() const;
	const Site& LocalSite() const;
	const InverterData::InverterMap& Inverters() const;
	std::vector<SecondaryMeter> SecondaryMeters() const;
	std::vector<SmartLoad> SmartLoads() const;

private:
	PowerFlowVersions m_PowerFlowVersion;
	Site m_LocalSite;
	InverterData::InverterMap m_Inverters;
	std::vector<SecondaryMeter> m_SecondaryMeters;
	std::vector<SmartLoad> m_SmartLoads;
};

#endif // SOLARAPI_CURRENTDATA_POWERFLOW_H

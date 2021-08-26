#ifndef SOLARAPI_CURRENTDATA_POWERFLOW_H
#define SOLARAPI_CURRENTDATA_POWERFLOW_H

#include <boost/property_tree/ptree.hpp>

#include <unordered_map>

#include "metering/devices/fronius/messages_types/inverter_data.h"
#include "metering/devices/fronius/messages_types/powerflow_versions.h"
#include "metering/devices/fronius/messages_types/secondary_meter_data.h"
#include "metering/devices/fronius/messages_types/smart_load_data.h"
#include "metering/devices/fronius/site/site.h"

class SolarApi_CurrentData_PowerFlow
{
public:
	explicit SolarApi_CurrentData_PowerFlow(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_PowerFlow() = default;

private:
	void ProcessPayload_Inverters(const boost::property_tree::ptree& node);
	void ProcessPayload_SmartLoads(const boost::property_tree::ptree& node);
	void ProcessPayload_SecondaryMeters(const boost::property_tree::ptree& node);

public:
	PowerFlowVersions PowerFlowVersion() const;
	const Site& LocalSite() const;

public:
	const std::unordered_map<HardwareBase::HardwareId, InverterData>& Inverters() const;
	const std::unordered_map<HardwareBase::HardwareId, SecondaryMeterData>& SecondaryMeters() const;
	const std::unordered_map<HardwareBase::HardwareId, SmartLoadData>& SmartLoads() const;

private:
	PowerFlowVersions m_PowerFlowVersion;
	Site m_LocalSite;

private:
	std::unordered_map<HardwareBase::HardwareId, InverterData> m_Inverters;
	std::unordered_map<HardwareBase::HardwareId, SecondaryMeterData> m_SecondaryMeters;
	std::unordered_map<HardwareBase::HardwareId, SmartLoadData> m_SmartLoads;
};

#endif // SOLARAPI_CURRENTDATA_POWERFLOW_H

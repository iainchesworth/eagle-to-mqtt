#ifndef SYMO_H
#define SYMO_H

#include <boost/property_tree/ptree.hpp>

#include <memory>
#include <vector>

#include "interfaces/idevice.h"
#include "interfaces/iserializer.h"
#include "interfaces/iserializable.h"
#include "metering/devices/fronius/common/device_stats.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_inverter.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_meter.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_sensorcard.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_stringcontrol.h"
#include "metering/devices/fronius/messages/solarapi_logdata_data.h"
#include "metering/devices/fronius/messages/solarapi_logdata_errorsandevents.h"
#include "metering/devices/fronius/messages/partial_message_types/inverter_data.h"
#include "metering/devices/fronius/messages/partial_message_types/powerflow_versions.h"
#include "metering/devices/fronius/messages/partial_message_types/secondary_meters.h"
#include "metering/devices/fronius/messages/partial_message_types/smartload.h"
#include "metering/devices/fronius/site/site.h"

class Symo : public IDevice
{
public:
	Symo();

public:
	void ProcessPayload(const boost::property_tree::ptree& node) override;

protected:
	virtual void ProcessFragment(const SolarApi_CurrentData_Inverter& solarapi_currentdata_inverter);
	virtual void ProcessFragment(const SolarApi_CurrentData_Meter& solarapi_currentdata_meter);
	virtual void ProcessFragment(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow);
	virtual void ProcessFragment(const SolarApi_CurrentData_SensorCard& solarapi_currentdata_sensorcard);
	virtual void ProcessFragment(const SolarApi_CurrentData_StringControl& solarapi_currentdata_stringcontrol);
	virtual void ProcessFragment(const SolarApi_LogData_Data& solarapi_logdata_data);
	virtual void ProcessFragment(const SolarApi_LogData_ErrorsAndEvents& solarapi_logdata_errorsandevents);
	virtual void ProcessHeaderAttributes(const boost::property_tree::ptree& header_attributes);

public:
	const Fronius::DeviceStatistics& Statistics() const;

private:
	Fronius::DeviceStatistics m_Statistics;

public:
	PowerFlowVersions PowerFlowVersion() const;
	Site LocalSite() const;
	std::vector<InverterData> Inverters() const;
	std::vector<SecondaryMeter> SecondaryMeters() const;
	std::vector<SmartLoad> SmartLoads() const;

private:
	PowerFlowVersions m_PowerFlowVersion;
	std::shared_ptr<Site> m_LocalSite;
	std::vector<InverterData> m_Inverters{};
	std::vector<SecondaryMeter> m_SecondaryMeters{};
	std::vector<SmartLoad> m_SmartLoads{};

public:
	friend class Symo_Serializer;
	boost::json::object Serialize() const override;
};

#endif // SYMO_H

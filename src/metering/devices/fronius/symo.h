#ifndef SYMO_H
#define SYMO_H

#include <boost/property_tree/ptree.hpp>

#include "interfaces/idevice.h"
#include "interfaces/iserializer.h"
#include "interfaces/iserializable.h"
#include "metering/devices/fronius/common/device_stats.h"
#include "metering/devices/fronius/energy_management/energy_production.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_inverter.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_meter.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_powerflow.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_sensorcard.h"
#include "metering/devices/fronius/messages/solarapi_currentdata_stringcontrol.h"
#include "metering/devices/fronius/messages/solarapi_logdata_data.h"
#include "metering/devices/fronius/messages/solarapi_logdata_errorsandevents.h"
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

private:
	void ProcessFragment_PowerFlow_Inverters(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow);
	void ProcessFragment_PowerFlow_Site(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow);
	void ProcessFragment_PowerFlow_SmartLoads(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow);
	void ProcessFragment_PowerFlow_SecondaryMeters(const SolarApi_CurrentData_PowerFlow& solarapi_currentdata_powerflow);

public:
	const Fronius::DeviceStatistics& Statistics() const;
	const Fronius::EnergyProduction& EnergyProduction() const;

private:
	Fronius::DeviceStatistics m_Statistics;
	Fronius::EnergyProduction m_EnergyProduction;

public:
	PowerFlowVersions PowerFlowVersion() const;

private:
	PowerFlowVersions m_PowerFlowVersion;

public:
	friend class Symo_Serializer;
	boost::json::object Serialize() const override;
};

#endif // SYMO_H

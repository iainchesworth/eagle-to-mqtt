#ifndef SOLARAPI_CURRENTDATA_INVERTER_H
#define SOLARAPI_CURRENTDATA_INVERTER_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/energy_management/energy_production_stats.h"
#include "metering/devices/fronius/hardware/hardware.h"
#include "metering/devices/fronius/messages/solarapi_base_message.h"
#include "metering/devices/fronius/messages_types/inverter_generation_data.h"

class SolarApi_CurrentData_Inverter : public SolarApi_Base_Message
{
public:
	explicit SolarApi_CurrentData_Inverter(const boost::property_tree::ptree& node);
	virtual ~SolarApi_CurrentData_Inverter() = default;

public:
	const InverterGenerationData& CurrentData() const;

private:
	InverterGenerationData m_CurrentData;
};

#endif // SOLARAPI_CURRENTDATA_INVERTER_H

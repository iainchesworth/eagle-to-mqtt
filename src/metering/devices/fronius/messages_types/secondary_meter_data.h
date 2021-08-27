#ifndef SECONDARY_METER_DATA_H
#define SECONDARY_METER_DATA_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/common/symo_payloads.h"

class SecondaryMeterData : public SymoPayload
{
public:
	SecondaryMeterData(const HardwareBase::HardwareId& id);

public:
	static SecondaryMeterData ExtractFromPayload(const boost::property_tree::ptree& node, const HardwareBase::HardwareId& id);
};

#endif // SECONDARY_METER_DATA_H

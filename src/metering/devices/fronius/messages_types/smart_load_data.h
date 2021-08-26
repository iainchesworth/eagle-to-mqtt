#ifndef SMART_LOAD_DATA_H
#define SMART_LOAD_DATA_H

#include <boost/property_tree/ptree.hpp>

#include "metering/devices/fronius/common/symo_payloads.h"

class SmartLoadData : public SymoPayload
{
public:
	SmartLoadData(const HardwareBase::HardwareId& id);

public:
	static SmartLoadData ExtractFromPayload(const boost::property_tree::ptree& node, const HardwareBase::HardwareId& id);
};

#endif // SMART_LOAD_DATA_H

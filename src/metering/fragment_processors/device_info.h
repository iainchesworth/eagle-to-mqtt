#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "interfaces/ifragmentprocessor.h"
#include "metering/common/protocol_types.h"
#include "metering/common/zigbee_mac_id.h"

class DeviceInfo : public IFragmentProcessor
{
public:
	DeviceInfo(const boost::property_tree::ptree& node);

private:
	ZigBeeMacId m_DeviceMacId;
	std::string m_InstallCode;
	std::string m_LinkKey;
	std::string m_FWVersion;
	std::string m_HWVersion;
	std::string m_ImageType;
	std::string m_Manufacturer;
	std::string m_ModelId;
	std::string m_DateCodeAndLotNumber;
	ProtocolTypes m_Protocol;
};

#endif // DEVICE_INFO_H

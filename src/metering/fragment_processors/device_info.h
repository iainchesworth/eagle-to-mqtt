#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <boost/property_tree/ptree.hpp>

#include <string>

#include "interfaces/ifragmentprocessor.h"

class DeviceInfo : public IFragmentProcessor
{
public:
	DeviceInfo(const boost::property_tree::ptree& node);
	virtual ~DeviceInfo();

public:
	std::string FirmwareVersion() const;
	std::string HardwareVersion() const;
	std::string ModelId() const;
	std::string ManufactureDate() const;
	std::string LotNumber() const;

private:
	std::string m_InstallCode;
	std::string m_LinkKey;
	std::string m_FWVersion;
	std::string m_HWVersion;
	std::string m_ImageType;
	std::string m_Manufacturer;
	std::string m_ModelId;
	std::string m_DateCode;
	std::string m_LotNumber;
};

#endif // DEVICE_INFO_H

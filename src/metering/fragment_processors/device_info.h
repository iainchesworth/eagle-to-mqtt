#ifndef DEVICE_INFO_H
#define DEVICE_INFO_H

#include <boost/property_tree/ptree.hpp>

#include <optional>
#include <string>

#include "interfaces/ifragmentprocessor.h"

class DeviceInfo : public IFragmentProcessor
{
	static const std::string FIELDNAME_INSTALLCODE;
	static const std::string FIELDNAME_LINKKEY;
	static const std::string FIELDNAME_FWVERSION;
	static const std::string FIELDNAME_HWVERISON;
	static const std::string FIELDNAME_IMAGETYPE;
	static const std::string FIELDNAME_MANUFACTURER;
	static const std::string FIELDNAME_MODELID;
	static const std::string FIELDNAME_DATECODE;

public:
	DeviceInfo(const boost::property_tree::ptree& node);
	virtual ~DeviceInfo();

public:
	std::optional<std::string> FirmwareVersion() const;
	std::optional<std::string> HardwareVersion() const;
	std::optional<std::string> ModelId() const;
	std::optional<std::string> ManufactureDate() const;
	std::optional<std::string> LotNumber() const;

private:
	std::optional<std::string> m_InstallCode;
	std::optional<std::string> m_LinkKey;
	std::optional<std::string> m_FWVersion;
	std::optional<std::string> m_HWVersion;
	std::optional<std::string> m_ImageType;
	std::optional<std::string> m_Manufacturer;
	std::optional<std::string> m_ModelId;
	std::optional<std::string> m_DateCode;
	std::optional<std::string> m_LotNumber;
};

#endif // DEVICE_INFO_H

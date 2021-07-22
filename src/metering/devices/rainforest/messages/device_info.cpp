#include <boost/log/trivial.hpp>

#include "metering/devices/rainforest/messages/device_info.h"
#include "metering/types/optional.h"

const std::string DeviceInfo::FIELDNAME_INSTALLCODE{ "InstallCode" };
const std::string DeviceInfo::FIELDNAME_LINKKEY{ "LinkKey" };
const std::string DeviceInfo::FIELDNAME_FWVERSION{ "FWVersion" };
const std::string DeviceInfo::FIELDNAME_HWVERISON{ "HWVersion" };
const std::string DeviceInfo::FIELDNAME_IMAGETYPE{ "ImageType" };
const std::string DeviceInfo::FIELDNAME_MANUFACTURER{ "Manufacturer" };
const std::string DeviceInfo::FIELDNAME_MODELID{ "ModelId" };
const std::string DeviceInfo::FIELDNAME_DATECODE{ "DateCode" };

DeviceInfo::DeviceInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_InstallCode(IsOptional<std::string>(node, FIELDNAME_INSTALLCODE)),
	m_LinkKey(IsOptional<std::string>(node, FIELDNAME_LINKKEY)),
	m_FWVersion(IsOptional<std::string>(node, FIELDNAME_FWVERSION)),
	m_HWVersion(IsOptional<std::string>(node, FIELDNAME_HWVERISON)),
	m_ImageType(IsOptional<std::string>(node, FIELDNAME_IMAGETYPE)),
	m_Manufacturer(IsOptional<std::string>(node, FIELDNAME_MANUFACTURER)),
	m_ModelId(IsOptional<std::string>(node, FIELDNAME_MODELID))
{
	// Manufacturer date code and lot number in format "YYYYMMDDZZZZZZZZ"

	const auto datecode_and_lotnumber = IsOptional<std::string>(node, FIELDNAME_DATECODE);
	if (!datecode_and_lotnumber.has_value())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Manufacturer date code and lot number don't exist in payload with key: DateCode";
	}
	else if (16 != datecode_and_lotnumber.value().length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Invalid length for manufacturer date code and lot number - expected 16; got " << datecode_and_lotnumber.value().length();
	}
	else
	{
		const auto datecode = std::string(datecode_and_lotnumber.value().begin(), datecode_and_lotnumber.value().begin() + 8);			// First 8 characters
		const auto lotnumber = std::string(datecode_and_lotnumber.value().begin() + 8, datecode_and_lotnumber.value().begin() + 16);	// Second 8 characters

		m_DateCode = datecode;
		m_LotNumber = lotnumber;
	}
}

std::optional<std::string> DeviceInfo::FirmwareVersion() const
{
	return m_FWVersion;
}

std::optional<std::string> DeviceInfo::HardwareVersion() const
{
	return m_HWVersion;
}

std::optional<std::string> DeviceInfo::ModelId() const
{
	return m_ModelId;
}

std::optional<std::string> DeviceInfo::ManufactureDate() const
{
	return m_DateCode;
}

std::optional<std::string> DeviceInfo::LotNumber() const
{
	return m_LotNumber;
}

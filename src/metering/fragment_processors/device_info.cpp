#include <boost/log/trivial.hpp>

#include "metering/fragment_processors/device_info.h"
#include "metering/type_handlers/essential.h"

DeviceInfo::DeviceInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(node),
	m_InstallCode(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("InstallCode"); })),
	m_LinkKey(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("LinkKey"); })),
	m_FWVersion(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("FWVersion"); })),
	m_HWVersion(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("HWVersion"); })),
	m_ImageType(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("ImageType"); })),
	m_Manufacturer(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("Manufacturer"); })),
	m_ModelId(IsEssential<std::string>([&node]() -> std::string { return node.get<std::string>("ModelId"); })),
	m_DateCode(),
	m_LotNumber()
{
	// Manufacturer date code and lot number in format "YYYYMMDDZZZZZZZZ"

	const auto datecode_and_lotnumber = node.get<std::string>("DateCode");
	if (16 != datecode_and_lotnumber.length())
	{
		BOOST_LOG_TRIVIAL(debug) << L"Invalid length for manufacturer date code and lot number - expected 16; got " << datecode_and_lotnumber.length();
	}
	else
	{
		const auto datecode = std::string(datecode_and_lotnumber.begin(), datecode_and_lotnumber.begin() + 8);			// First 8 characters
		const auto lotnumber = std::string(datecode_and_lotnumber.begin() + 8, datecode_and_lotnumber.begin() + 16);	// Second 8 characters

		m_DateCode = datecode;
		m_LotNumber = lotnumber;
	}
}

DeviceInfo::~DeviceInfo()
{
}

std::string DeviceInfo::FirmwareVersion() const
{
	return m_FWVersion;
}

std::string DeviceInfo::HardwareVersion() const
{
	return m_HWVersion;
}

std::string DeviceInfo::ModelId() const
{
	return m_ModelId;
}

std::string DeviceInfo::ManufactureDate() const
{
	return m_DateCode;
}

std::string DeviceInfo::LotNumber() const
{
	return m_LotNumber;
}

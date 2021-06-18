#include <boost/log/trivial.hpp>
#include <boost/optional/optional.hpp>

#include "metering/fragment_processors/device_info.h"

DeviceInfo::DeviceInfo(const boost::property_tree::ptree& node) :
	IFragmentProcessor(),
	m_DeviceMacId(node.get<std::string>("DeviceMacId")),
	m_InstallCode(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "InstallCode", "")),
	m_LinkKey(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "LinkKey", "")),
	m_FWVersion(node.get<std::string>("FWVersion")),
	m_HWVersion(node.get<std::string>("HWVersion")),
	m_ImageType(node.get<std::string>("ImageType")),
	m_Manufacturer(node.get<std::string>("Manufacturer")),
	m_ModelId(IFragmentProcessor::ProcessOptionalTag<std::string>(node, "ModelId", "")),
	m_DateCodeAndLotNumber(node.get<std::string>("DateCode")),
	m_Protocol{ IFragmentProcessor::ProcessOptionalProtocol(node) }
{
}

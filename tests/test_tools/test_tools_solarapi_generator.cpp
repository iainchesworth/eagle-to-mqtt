#include <stdexcept>

#include "test_tools/test_tools_solarapi_generator.h"

test_tools::SolarApi_Generator::SolarApi_Generator(SolarApiVersions version) :
	m_Version(version)
{
}

std::string test_tools::SolarApi_Generator::Generate_CurrentData_Inverter() const
{
    switch (m_Version)
    {
    case SolarApiVersions::FroniusHybrid:
        return Generate_CurrentData_Inverter_Hybrid();
    case SolarApiVersions::FroniusNonHybrid:
        return Generate_CurrentData_Inverter_NonHybrid();
    case SolarApiVersions::GEN24_Primo:
        return Generate_CurrentData_Inverter_GEN24();
	default:
		throw std::runtime_error("Generate_CurrentData_Inverter(): Invalid version present in the SOLAR API Generator test tool");
	}
}

std::string test_tools::SolarApi_Generator::Generate_CurrentData_PowerFlow() const
{
    switch (m_Version)
    {
    case SolarApiVersions::FroniusHybrid:
        return Generate_CurrentData_PowerFlow_Hybrid();
    case SolarApiVersions::FroniusNonHybrid:
        return Generate_CurrentData_PowerFlow_NonHybrid();
    case SolarApiVersions::GEN24_Primo:
        return Generate_CurrentData_PowerFlow_GEN24();
    default:
        throw std::runtime_error("Generate_CurrentData_PowerFlow(): Invalid version present in the SOLAR API Generator test tool");
    }
}

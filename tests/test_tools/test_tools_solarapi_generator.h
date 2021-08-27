#ifndef TEST_TOOLS_SOLARAPI_GENERATOR_H
#define TEST_TOOLS_SOLARAPI_GENERATOR_H

#include <string>

namespace test_tools
{

class SolarApi_Generator
{
public:
	enum class SolarApiVersions
	{
		FroniusHybrid,
		FroniusNonHybrid,
		GEN24_Primo
	};

public:
	explicit SolarApi_Generator(SolarApiVersions version);

public:
	std::string Generate_CurrentData_Inverter() const;
	std::string Generate_CurrentData_PowerFlow() const;

private:
	std::string Generate_CurrentData_Inverter_Hybrid() const;
	std::string Generate_CurrentData_PowerFlow_Hybrid() const;

private:
	std::string Generate_CurrentData_Inverter_NonHybrid() const;
	std::string Generate_CurrentData_PowerFlow_NonHybrid() const;

private:
	std::string Generate_CurrentData_Inverter_GEN24() const;
	std::string Generate_CurrentData_PowerFlow_GEN24() const;

private:
	SolarApiVersions m_Version;
};

}
// namespace test_tools

#endif // TEST_TOOLS_SOLARAPI_GENERATOR_H

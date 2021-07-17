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
		V0, V1, V2
	};

public:
	SolarApi_Generator(SolarApiVersions version);

public:
	std::string Generate_CurrentData_Inverter() const;

private:
	SolarApiVersions m_Version;
};

}
// namespace test_tools

#endif // TEST_TOOLS_SOLARAPI_GENERATOR_H

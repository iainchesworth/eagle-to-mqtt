#ifndef TEST_TOOLS_FRAGMENT_GENERATOR_H
#define TEST_TOOLS_FRAGMENT_GENERATOR_H

#include <sstream>
#include <string>

namespace test_tools
{

class FragmentGenerator
{
	static const std::string HEADER_V1;
	static const std::string HEADER_V2;
	static const std::string FOOTER;

public:
	enum class FragmentVersions
	{
		V1, V2
	};

public:
	FragmentGenerator(FragmentVersions version);

public:
	FragmentGenerator& AddFragment_ConnectionStatus();
	FragmentGenerator& AddFragment_CurrentSummation();
	FragmentGenerator& AddFragment_DeviceInfo();
	FragmentGenerator& AddFragment_InstantaneousDemand();
	FragmentGenerator& AddFragment_MessageCluster();
	FragmentGenerator& AddFragment_NetworkInfo();
	FragmentGenerator& AddFragment_PriceCluster();

public:
	std::stringstream Generate() const;

private:
	FragmentVersions m_Version;
	std::string m_Fragment;
};

}
// namespace test_tools

#endif // TEST_TOOLS_FRAGMENT_GENERATOR_H

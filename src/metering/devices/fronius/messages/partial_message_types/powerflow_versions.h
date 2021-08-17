#ifndef POWERFLOW_VERSIONS_H
#define POWERFLOW_VERSIONS_H

#include <cstdint>
#include <ostream>
#include <string>

class PowerFlowVersions
{
	static const std::string NOT_SPECIFIED;
	static const std::string VERSION_10;
	static const std::string VERSION_11;
	static const std::string VERSION_12;
	static const std::string UNKNOWN;

public:
	enum class Versions
	{
		NotSpecified = 0,
		Version10 = 10,
		Version11 = 11,
		Version12 = 12,
		Unknown = -1
	};

public:
	PowerFlowVersions();
	explicit PowerFlowVersions(Versions version);
	explicit PowerFlowVersions(int32_t version);

private:
	Versions m_Version;

public:
	static Versions FromInteger(const int32_t version_integer);
	static std::string ToString(const Versions version);

public:
	Versions operator()() const;

public:
	bool operator==(const PowerFlowVersions& powerflow_version) const;
	bool operator==(const Versions& version) const;

public:
	friend bool operator<(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right);
	friend bool operator>(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right);
	friend bool operator<=(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right);
	friend bool operator>=(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right);
	friend std::ostream& operator<<(std::ostream& os, const PowerFlowVersions& powerflow_version);
};

#endif // POWERFLOW_VERSIONS_H

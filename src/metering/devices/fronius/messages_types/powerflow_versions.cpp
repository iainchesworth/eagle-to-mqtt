#include <spdlog/spdlog.h>

#include "metering/devices/fronius/messages_types/powerflow_versions.h"

const std::string PowerFlowVersions::NOT_SPECIFIED{ "Not Specified" };
const std::string PowerFlowVersions::VERSION_10{ "Version 10" };
const std::string PowerFlowVersions::VERSION_11{ "Version 11" };
const std::string PowerFlowVersions::VERSION_12{ "Version 12" };
const std::string PowerFlowVersions::UNKNOWN{ "Unknown" };

PowerFlowVersions::PowerFlowVersions() :
	PowerFlowVersions(Versions::NotSpecified)
{
}

PowerFlowVersions::PowerFlowVersions(Versions version) :
	m_Version(version)
{
}

PowerFlowVersions::PowerFlowVersions(int32_t version) :
	PowerFlowVersions(FromInteger(version))
{
}

PowerFlowVersions::Versions PowerFlowVersions::FromInteger(const int32_t version_integer)
{
	Versions version_type = Versions::NotSpecified;

	switch (version_integer)
	{
	case static_cast<int32_t>(Versions::NotSpecified):
		version_type = Versions::NotSpecified;
		break;
	case static_cast<int32_t>(Versions::Version10):
		version_type = Versions::Version10;
		break;
	case static_cast<int32_t>(Versions::Version11):
		version_type = Versions::Version11;
		break;
	case static_cast<int32_t>(Versions::Version12):
		version_type = Versions::Version12;
		break;
	case static_cast<int32_t>(Versions::Unknown):
	default:
		spdlog::warn("Unknown Version provided to converter: {}", version_integer);
		version_type = Versions::Unknown;
		break;
	}

	return version_type;
}

std::string PowerFlowVersions::ToString(const Versions version)
{
	switch (version)
	{
	case Versions::NotSpecified:
		return NOT_SPECIFIED;
	case Versions::Version10:
		return VERSION_10;
	case Versions::Version11:
		return VERSION_11;
	case Versions::Version12:
		return VERSION_12;
	case Versions::Unknown:
	default:
		return UNKNOWN;
	}
}

PowerFlowVersions::Versions PowerFlowVersions::operator()() const
{
	return m_Version;
}

bool PowerFlowVersions::operator==(const PowerFlowVersions& powerflow_version) const
{
	return (m_Version == powerflow_version.m_Version);
}

bool PowerFlowVersions::operator==(const Versions& version) const
{
	return (m_Version == version);
}

bool operator<(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right)
{
	return (version_left < version_right.m_Version);
}

bool operator>(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right)
{
	return (version_left > version_right.m_Version);
}

bool operator<=(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right)
{
	return (version_left <= version_right.m_Version);
}

bool operator>=(const PowerFlowVersions::Versions& version_left, const PowerFlowVersions& version_right)
{
	return (version_left >= version_right.m_Version);
}

std::ostream& operator<<(std::ostream& os, const PowerFlowVersions& powerflow_version)
{
	os << PowerFlowVersions::ToString(powerflow_version.m_Version);
	return os;
}
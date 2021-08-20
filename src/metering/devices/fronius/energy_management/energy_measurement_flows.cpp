#include <spdlog/spdlog.h>

#include <string>

#include "metering/devices/fronius/energy_management/energy_measurement_flows.h"

EnergyFlowBase<GridFlowDirections>::FlowMeanings GridFlow::Value_ZeroOrMore() const
{
	return GridFlowDirections::FromGrid;
}

EnergyFlowBase<GridFlowDirections>::FlowMeanings GridFlow::Value_LessThanZero() const 
{
	return GridFlowDirections::ToGrid;
}

std::ostream& operator<<(std::ostream& os, GridFlowDirections direction)
{
	static const std::string FROM_GRID{ "FromGrid" };
	static const std::string TO_GRID{ "ToGrid" };

	switch (direction)
	{
	case GridFlowDirections::FromGrid: os << FROM_GRID; break;
	case GridFlowDirections::ToGrid: os << TO_GRID; break;
	default: spdlog::debug("Invalid GridFlowDirections value: {}", direction); break;
	}

	return os;
}

EnergyFlowBase<LoadFlowDirections>::FlowMeanings LoadFlow::Value_ZeroOrMore() const
{
	return LoadFlowDirections::Producer;
}

EnergyFlowBase<LoadFlowDirections>::FlowMeanings LoadFlow::Value_LessThanZero() const
{
	return LoadFlowDirections::Consumer;
}

std::ostream& operator<<(std::ostream& os, LoadFlowDirections direction)
{
	static const std::string PRODUCER{ "Producer" };
	static const std::string CONSUMER{ "Consumer" };

	switch (direction)
	{
	case LoadFlowDirections::Producer: os << PRODUCER; break;
	case LoadFlowDirections::Consumer: os << CONSUMER; break;
	default: spdlog::debug("Invalid LoadFlowDirections value: {}", direction); break;
	}

	return os;
}

EnergyFlowBase<ChargeFlowDirections>::FlowMeanings ChargeFlow::Value_ZeroOrMore() const
{
	return ChargeFlowDirections::Discharging;
}

EnergyFlowBase<ChargeFlowDirections>::FlowMeanings ChargeFlow::Value_LessThanZero() const
{
	return ChargeFlowDirections::Charging;
}

std::ostream& operator<<(std::ostream& os, ChargeFlowDirections direction)
{
	static const std::string DISCHARGING{ "Discharging" };
	static const std::string CHARGING{ "Charging" };

	switch (direction)
	{
	case ChargeFlowDirections::Discharging: os << DISCHARGING; break;
	case ChargeFlowDirections::Charging: os << CHARGING; break;
	default: spdlog::debug("Invalid ChargeFlowDirections value: {}", direction); break;
	}

	return os;
}

EnergyFlowBase<ProductionFlowDirections>::FlowMeanings ProductionFlow::Value_ZeroOrMore() const
{
	return ProductionFlowDirections::Producing;
}

EnergyFlowBase<ProductionFlowDirections>::FlowMeanings ProductionFlow::Value_LessThanZero() const
{
	return ProductionFlowDirections::Unknown;
}

std::ostream& operator<<(std::ostream& os, ProductionFlowDirections direction)
{
	static const std::string PRODUCING{ "Producing" };
	static const std::string UNKNOWN{ "Unknown" };

	switch (direction)
	{
	case ProductionFlowDirections::Producing: os << PRODUCING; break;
	case ProductionFlowDirections::Unknown: os << UNKNOWN; break;
	default: spdlog::debug("Invalid ProductionFlowDirections value: {}", direction); break;
	}

	return os;
}

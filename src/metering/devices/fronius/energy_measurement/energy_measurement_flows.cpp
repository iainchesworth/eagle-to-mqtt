#include "metering/devices/fronius/energy_measurement/energy_measurement_flows.h"

EnergyFlowBase<GridFlowDirections>::FlowMeanings GridFlow::Value_ZeroOrMore() const
{
	return GridFlowDirections::FromGrid;
}

EnergyFlowBase<GridFlowDirections>::FlowMeanings GridFlow::Value_LessThanZero() const 
{
	return GridFlowDirections::ToGrid;
}

EnergyFlowBase<LoadFlowDirections>::FlowMeanings LoadFlow::Value_ZeroOrMore() const
{
	return LoadFlowDirections::Producer;
}

EnergyFlowBase<LoadFlowDirections>::FlowMeanings LoadFlow::Value_LessThanZero() const
{
	return LoadFlowDirections::Consumer;
}

EnergyFlowBase<ChargeFlowDirections>::FlowMeanings ChargeFlow::Value_ZeroOrMore() const
{
	return ChargeFlowDirections::Discharging;
}

EnergyFlowBase<ChargeFlowDirections>::FlowMeanings ChargeFlow::Value_LessThanZero() const
{
	return ChargeFlowDirections::Charging;
}

EnergyFlowBase<ProductionFlowDirections>::FlowMeanings ProductionFlow::Value_ZeroOrMore() const
{
	return ProductionFlowDirections::Producing;
}

EnergyFlowBase<ProductionFlowDirections>::FlowMeanings ProductionFlow::Value_LessThanZero() const
{
	return ProductionFlowDirections::Unknown;
}

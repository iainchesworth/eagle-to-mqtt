#ifndef ENERGY_MEASUREMENT_FLOWS_H
#define ENERGY_MEASUREMENT_FLOWS_H

#include <cmath>
#include <ostream>

template<typename FLOW_DIRECTIONS>
class EnergyFlowBase
{
public:
	using FlowMeanings = FLOW_DIRECTIONS;

public:
	FlowMeanings operator()(double energy_measurement_value) const
	{
		if (std::isless(energy_measurement_value, 0.0f))
		{
			return Value_LessThanZero();
		}
		else
		{
			return Value_ZeroOrMore();
		}
	}

protected:
	virtual FlowMeanings Value_ZeroOrMore() const = 0;
	virtual FlowMeanings Value_LessThanZero() const = 0;
};

//-----------------------------------------------------------------------------
//
// Power flows
//
//-----------------------------------------------------------------------------

enum class GridFlowDirections
{
	FromGrid,	// Positive
	ToGrid		// Negative
};

class GridFlow : public EnergyFlowBase<GridFlowDirections>
{
private:
	FlowMeanings Value_ZeroOrMore() const final;
	FlowMeanings Value_LessThanZero() const final;
};

std::ostream& operator<<(std::ostream& os, GridFlowDirections direction);

//-----------------------------------------------------------------------------
//
// Power flows
//
//-----------------------------------------------------------------------------

enum class LoadFlowDirections
{
	Producer,	// Positive
	Consumer	// Negative
};

class LoadFlow : public EnergyFlowBase<LoadFlowDirections>
{
private:
	FlowMeanings Value_ZeroOrMore() const final;
	FlowMeanings Value_LessThanZero() const final;
};

std::ostream& operator<<(std::ostream& os, LoadFlowDirections direction);

//-----------------------------------------------------------------------------
//
// Power flows
//
//-----------------------------------------------------------------------------

enum class ChargeFlowDirections
{
	Discharging,	// Positive
	Charging		// Negative
};

class ChargeFlow : public EnergyFlowBase<ChargeFlowDirections>
{
private:
	FlowMeanings Value_ZeroOrMore() const final;
	FlowMeanings Value_LessThanZero() const final;
};

std::ostream& operator<<(std::ostream& os, ChargeFlowDirections direction);

//-----------------------------------------------------------------------------
//
// Power flows
//
//-----------------------------------------------------------------------------

enum class ProductionFlowDirections
{
	Producing,	// Positive
	Unknown		// Negative
};

class ProductionFlow : public EnergyFlowBase<ProductionFlowDirections>
{
private:
	FlowMeanings Value_ZeroOrMore() const final;
	FlowMeanings Value_LessThanZero() const final;
};

std::ostream& operator<<(std::ostream& os, ProductionFlowDirections direction);

#endif // ENERGY_MEASUREMENT_FLOWS_H

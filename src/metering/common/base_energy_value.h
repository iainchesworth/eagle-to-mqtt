#ifndef BASE_ENERGY_VALUE_H
#define BASE_ENERGY_VALUE_H

class BaseEnergyValue
{
protected:
	BaseEnergyValue();

public:
	explicit BaseEnergyValue(double energy_value);

public:
	virtual double EnergyValue() const;

protected:
	double m_EnergyValue;
};

#endif // BASE_ENERGY_VALUE_H

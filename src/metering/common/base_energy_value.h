#ifndef BASE_ENERGY_VALUE_H
#define BASE_ENERGY_VALUE_H

class BaseEnergyValue
{
protected:
	BaseEnergyValue();

public:
	BaseEnergyValue(double energy_value);
	virtual ~BaseEnergyValue();

public:
	virtual double EnergyValue() const;

protected:
	double m_EnergyValue;
};

#endif // BASE_ENERGY_VALUE_H

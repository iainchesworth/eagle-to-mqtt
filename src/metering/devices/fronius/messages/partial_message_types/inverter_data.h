#ifndef INVERTER_DATA_H
#define INVERTER_DATA_H

#include <boost/property_tree/ptree.hpp>

class InverterData
{
public:
	InverterData();

private:
	/*DeviceType;
	Power_InWatts;
	StateOfCharge_Percentage;
	ComponentIdentification;
	BatteryMode;
	GeneratedEnergy_Day_InWattHours;
	GeneratedEnergy_Year_InWattHours;
	GeneratedEnergy_Total_InWattHours;*/

public:
	static InverterData ExtractFromPayload(const boost::property_tree::ptree& node);
};

#endif // INVERTER_DATA_H

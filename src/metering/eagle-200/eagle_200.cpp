#include "metering/eagle-200/eagle_200.h"

Eagle200::Eagle200() : 
	IEagle()
{

}

void Eagle200::ProcessFragment(const DeviceInfo& device_info)
{
	IEagle::ProcessFragment(device_info);
}

void Eagle200::ProcessFragment(const InstantaneousDemand& instantaneous_demand)
{
	IEagle::ProcessFragment(instantaneous_demand);
}

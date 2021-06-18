#ifndef EAGLE_200_H
#define EAGLE_200_H

#include "interfaces/ieagle.h"

class Eagle200 : public IEagle
{
public:
	Eagle200();

public:
	virtual void ProcessFragment(const DeviceInfo& device_info) final;
	virtual void ProcessFragment(const InstantaneousDemand& instantaneous_demand) final;
};

#endif // EAGLE_200_H

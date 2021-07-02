#ifndef EAGLE_200_H
#define EAGLE_200_H

#include "metering/devices/eagle.h"

class Eagle200 : public Eagle
{
public:
	Eagle200();

private:
	virtual void ProcessFragment(const NetworkInfo& network_info) final;
};

#endif // EAGLE_200_H

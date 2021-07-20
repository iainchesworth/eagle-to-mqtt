#ifndef EAGLE_200_H
#define EAGLE_200_H

#include "metering/devices/rainforest/eagle.h"

class Eagle200 : public Eagle
{
public:
	Eagle200();

private:
	void ProcessFragment(const NetworkInfo& network_info) final;
};

#endif // EAGLE_200_H

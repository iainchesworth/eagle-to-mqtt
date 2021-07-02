#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include <boost/log/trivial.hpp>

#include <memory>

#include "exceptions/not_implemented.h"
#include "metering/devices/eagle.h"
#include "metering/devices/eagle-200/eagle_200.h"
#include "metering/devices/rfa-z109/rfa_z109.h"

namespace DeviceFactory
{
	template<typename T> std::shared_ptr<Eagle> CreateDevice();
	template<> std::shared_ptr<Eagle> CreateDevice<Eagle200>();
	template<> std::shared_ptr<Eagle> CreateDevice<RFA_Z109>();
};

#endif // DEVICE_FACTORY_H

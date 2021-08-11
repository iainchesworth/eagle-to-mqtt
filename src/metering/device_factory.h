#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include <spdlog/spdlog.h>

#include <memory>
#include <type_traits>

#include "exceptions/not_implemented.h"
#include "interfaces/idevice.h"

namespace DeviceFactory
{
	template<typename DEVICE_TYPE, typename std::enable_if_t<std::is_base_of_v<IDevice, DEVICE_TYPE>>* = nullptr>
	std::unique_ptr<DEVICE_TYPE> CreateDevice()
	{
		spdlog::debug("Factory is creating new device of type: {}", typeid(DEVICE_TYPE).name());
		return std::make_unique<DEVICE_TYPE>();
	}
};

#endif // DEVICE_FACTORY_H

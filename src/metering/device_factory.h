#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include <boost/log/trivial.hpp>

#include <memory>
#include <type_traits>

#include "exceptions/not_implemented.h"
#include "interfaces/idevice.h"

namespace DeviceFactory
{
	template<typename DEVICE_TYPE, typename std::enable_if_t<std::is_base_of_v<IDevice, DEVICE_TYPE>>* = nullptr>
	std::unique_ptr<DEVICE_TYPE> CreateDevice()
	{
		BOOST_LOG_TRIVIAL(debug) << L"Factory is creating new device of type: " << typeid(DEVICE_TYPE).name();
		return std::make_unique<DEVICE_TYPE>();
	}
};

#endif // DEVICE_FACTORY_H

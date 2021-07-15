#ifndef DEVICE_FACTORY_H
#define DEVICE_FACTORY_H

#include <boost/log/trivial.hpp>

#include <memory>
#include <type_traits>

#include "exceptions/not_implemented.h"
#include "interfaces/idevice.h"

namespace DeviceFactory
{
	template<typename DEVICE_TYPE, typename std::enable_if<std::is_base_of<IDevice, DEVICE_TYPE>::value>::type* = nullptr>
	std::unique_ptr<DEVICE_TYPE> CreateDevice()
	{
		// BOOST_LOG_TRIVIAL(warning) << L"Attempted to create an instance of an unknown device type";
		return std::make_unique<DEVICE_TYPE>();
	}
};

#endif // DEVICE_FACTORY_H

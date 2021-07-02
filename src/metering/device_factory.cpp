#include "metering/device_factory.h"

template<typename T>
std::shared_ptr<Eagle> DeviceFactory::CreateDevice()
{
	BOOST_LOG_TRIVIAL(warning) << L"Attempted to create an instance of an unknown device type";
	throw NotImplemented();
}

template<>
std::shared_ptr<Eagle> DeviceFactory::CreateDevice<Eagle200>()
{
	BOOST_LOG_TRIVIAL(trace) << L"Creating a new instance of an Eagle-200 device";
	return std::make_shared<Eagle200>();
}

template<>
std::shared_ptr<Eagle> DeviceFactory::CreateDevice<RFA_Z109>()
{
	BOOST_LOG_TRIVIAL(trace) << L"Creating a new instance of an RFA-Z109 device";
	return std::make_shared<RFA_Z109>();
}

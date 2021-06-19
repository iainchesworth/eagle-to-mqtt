#ifndef DEVICE_IDENTIFIER_H
#define DEVICE_IDENTIFIER_H

#include <boost/property_tree/ptree.hpp>

#include <memory>

std::shared_ptr<IEagle> IdentifyAndGetDeviceInstance(boost::property_tree::ptree& device_payload);

#endif // DEVICE_IDENTIFIER_H

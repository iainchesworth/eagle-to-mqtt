#ifndef DEVICE_IDENTIFIER_H
#define DEVICE_IDENTIFIER_H

#include <boost/property_tree/ptree.hpp>

#include <memory>

#include "metering/devices/eagle.h"

std::shared_ptr<Eagle> IdentifyAndGetDeviceInstance(boost::property_tree::ptree& device_payload);

#endif // DEVICE_IDENTIFIER_H

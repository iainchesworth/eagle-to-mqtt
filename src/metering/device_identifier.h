#ifndef DEVICE_IDENTIFIER_H
#define DEVICE_IDENTIFIER_H

#include <boost/property_tree/ptree.hpp>

#include <memory>

// Forward declarations
class IDevice;

std::shared_ptr<IDevice> IdentifyAndGetEagleInstance(const boost::property_tree::ptree& device_payload);
std::shared_ptr<IDevice> IdentifyAndGetSymoInstance(const boost::property_tree::ptree& device_payload);

#endif // DEVICE_IDENTIFIER_H

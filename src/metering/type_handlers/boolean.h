#ifndef BOOLEAN_H
#define BOOLEAN_H

#include <boost/property_tree/ptree.hpp>

#include <string>

bool GetValue_Boolean(const boost::property_tree::ptree& node, const std::string& key);

#endif // BOOLEAN_H

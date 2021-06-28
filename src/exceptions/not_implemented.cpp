#include "exceptions/not_implemented.h"

NotImplemented::NotImplemented() :
	std::runtime_error("Feature is not currently implemented")
{
}

NotImplemented::NotImplemented(const std::string& message) :
	std::runtime_error(message)
{
}

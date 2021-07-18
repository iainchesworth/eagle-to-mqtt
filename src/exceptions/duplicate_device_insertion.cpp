#include "exceptions/duplicate_device_insertion.h"

DuplicateDeviceInsertion::DuplicateDeviceInsertion() :
	std::runtime_error("Attempted to insert an already existing device into the registry")
{
}

DuplicateDeviceInsertion::~DuplicateDeviceInsertion()
{
}

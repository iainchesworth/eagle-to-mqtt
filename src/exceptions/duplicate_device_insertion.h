#ifndef DUPLICATE_DEVICE_INSERTION_H
#define DUPLICATE_DEVICE_INSERTION_H

#include <stdexcept>

class DuplicateDeviceInsertion : public std::runtime_error
{
public:
	DuplicateDeviceInsertion();
	virtual ~DuplicateDeviceInsertion() = default;
};

#endif // DUPLICATE_DEVICE_INSERTION_H

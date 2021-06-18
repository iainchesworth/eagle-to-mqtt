#ifndef NOT_IMPLEMENTED_H
#define NOT_IMPLEMENTED_H

#include <stdexcept>

class NotImplemented : public std::runtime_error
{
public:
	NotImplemented();
};

#endif // UNKNOWN_FRAGMENT_TYPE_H

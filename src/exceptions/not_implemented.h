#ifndef NOT_IMPLEMENTED_H
#define NOT_IMPLEMENTED_H

#include <stdexcept>
#include <string>

class NotImplemented : public std::runtime_error
{
public:
	NotImplemented();
	NotImplemented(const std::string& message);
};

#endif // UNKNOWN_FRAGMENT_TYPE_H

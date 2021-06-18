#include "exceptions/not_implemented.h"

NotImplemented::NotImplemented() :
	std::runtime_error("Feature is not currently implemented")
{
}

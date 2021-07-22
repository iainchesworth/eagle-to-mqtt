#ifndef MISSING_RAINFOREST_NODE_H
#define MISSING_RAINFOREST_NODE_H

#include <stdexcept>

class MissingRainforestNode : public std::runtime_error
{
public:
	MissingRainforestNode();
};


#endif // MISSING_RAINFOREST_NODE_H
